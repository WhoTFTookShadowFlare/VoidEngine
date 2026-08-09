#include "class_holder.hpp"

#include "lua.h"
#include "lualib.h"
#include "object_holder.hpp"
#include "method_holder.hpp"
#include "property_holder.hpp"
#include "event_handler_holder.hpp"

#include <print>
#include "ve/class_db.hpp"
#include "../luau_script_engine.hpp"

namespace VoidEngine::Scripts::Luau {
	int ClassNew(lua_State* L) {
		if(!lua_isstring(L, 1)) {
			std::println("[ERR] [LUAU] Class.new takes only a string for class name");
			return 0;
		}

		const Class* super = nullptr;
		if(lua_isstring(L, 2)) {
			super = ClassDB::getInstance()->getClassByName(luaL_checkstring(L, 2));
		} else {
			ClassHolder* clsHolder = static_cast<ClassHolder*>(luaL_checkudata(L, 2, "Class"));
			super = clsHolder->cls;
		}

		const char* name = luaL_checkstring(L, 1);
		if(name == nullptr) return 0;

		if(super == nullptr) {
			std::println("[ERR] [LUAU] No super for class {}", name);
			return 0;
		}

		ClassHolder* ptr = static_cast<ClassHolder*>(lua_newuserdatadtor(L, sizeof(ClassHolder), [](void* data) {
			ClassHolder* cls = static_cast<ClassHolder*>(data);
			if(ClassDB::getInstance()->getClassByName(cls->cls->name) != cls->cls) {
				std::println("[WARN] Class {} was instanced but not registered!", cls->cls->name);
				delete cls->cls;
			}
		}));

		if(luaL_newmetatable(L, "Class")) {
			luaL_register(L, nullptr, classMeth);
			lua_pushliteral(L, "Class");
			lua_rawsetfield(L, -2, "__type");
		}
		lua_setmetatable(L, -2);

		Class* cls = new Class;
		cls->name = name;
		cls->super = super;
		ptr->cls = cls;

		return 1;
	}

	int GetClass(lua_State* L) {
		if(!lua_isstring(L, 1)) {
			std::println("[ERR] [LUAU] Class.get takes only a string for class name");
			return 0;
		}

		const char* name = luaL_checkstring(L, 1);
		if(name == nullptr) return 0;

		const Class* cls = ClassDB::getInstance()->getClassByName(name);
		ClassHolder* ptr = static_cast<ClassHolder*>(lua_newuserdata(L, sizeof(ClassHolder)));
		ptr->cls = cls;

		if(luaL_newmetatable(L, "Class")) {
			luaL_register(L, nullptr, classMeth);
			lua_pushliteral(L, "Class");
			lua_rawsetfield(L, -2, "__type");
		}
		lua_setmetatable(L, -2);

		return 1;
	}

	int RegisterClass(lua_State* L) {
		ClassHolder* cls = (ClassHolder*) luaL_checkudata(L, 1, "Class");
		ClassDB::getInstance()->registerClass(cls->cls);
		return 0;
	}

	int ClassToString(lua_State* L) {
		ClassHolder* cls = static_cast<ClassHolder*>(lua_touserdata(L, 1));
		lua_pushstring(L, cls->cls->name);
		return 1;
	}
	
	int ClassGet(lua_State* L) {
		return 0;
	}
	
	int ClassSet(lua_State* L) {
		return 0;
	}
	
	int ClassCall(lua_State* L) {
		std::string fnName = lua_namecallatom(L, nullptr);

		if(fnName == "addproperty") return ClassAddProperty(L);
		if(fnName == "addmethod") return ClassAddMethod(L);
		if(fnName == "addeventhandler") return ClassAddEventHandler(L);
		if(fnName == "findproperty") return ClassFindProperty(L);
		if(fnName == "findmethod") return ClassFindMethod(L);
		if(fnName == "findeventhandler") return ClassFindEventHandler(L);

		// setconstructor
		if(fnName == "isabstract") return ClassIsAbstract(L);
		if(fnName == "instanceof") return ClassInstanceOf(L);
		if(fnName == "create") return ClassCreate(L);
		return 0;
	}

	int ClassEq(lua_State* L) {
		if(!lua_istable(L, 2)) {
			lua_pushboolean(L, false);
			return 1;
		}

		try {
			ClassHolder* LHS = static_cast<ClassHolder*>(luaL_checkudata(L, 1, "Class"));
			ClassHolder* RHS = static_cast<ClassHolder*>(luaL_checkudata(L, 2, "Class"));
			lua_pushboolean(L, LHS->cls == RHS->cls);
			return 1;
		} catch(std::exception& ex) {	}

		lua_pushboolean(L, false);
		return 1;
	}

	int ClassAddMethod(lua_State* L) {
		ClassHolder* clsHolder = static_cast<ClassHolder*>(luaL_checkudata(L, 1, "Class"));
		const MethodBase* meth = static_cast<MethodBase*>(luaL_checkudata(L, 2, "Method"));

		Class* cls = const_cast<Class*>(clsHolder->cls);
		cls->methods.push_back(meth);
		return 0;
	}

	int ClassAddProperty(lua_State* L) {
		ClassHolder* clsHolder = static_cast<ClassHolder*>(luaL_checkudata(L, 1, "Class"));
		const PropertyBase* prop = static_cast<PropertyBase*>(luaL_checkudata(L, 2, "Property"));

		Class* cls = const_cast<Class*>(clsHolder->cls);
		cls->properties.push_back(prop);
		return 0;
	}

	int ClassAddEventHandler(lua_State* L) {
		ClassHolder* clsHolder = static_cast<ClassHolder*>(luaL_checkudata(L, 1, "Class"));
		const EventHandlerHolder* evtHandler = static_cast<EventHandlerHolder*>(luaL_checkudata(L, 2, "EventHandler"));

		Class* cls = const_cast<Class*>(clsHolder->cls);
		cls->eventHandlers.push_back(evtHandler->handler);
		return 0;
	}

	int ClassFindProperty(lua_State* L) {
		ClassHolder* cls = (ClassHolder*) lua_touserdata(L, 1);
		if(!lua_isstring(L, 2)) {
			std::println("[ERR] [LUAU] Class:findproperty(name) name must be a string");
			return 0;
		}

		std::string name = luaL_checkstring(L, 2);

		const PropertyBase* prop = cls->cls->findProperty(name);
		if(prop == nullptr) {
			lua_pushnil(L);
			return 1;
		}

		PropertyHolder* propHolder = static_cast<PropertyHolder*>(lua_newuserdata(L, sizeof(PropertyHolder)));
		if(luaL_newmetatable(L, "Property")) {
			luaL_register(L, nullptr, propertyMeth);
			lua_pushliteral(L, "Property");
			lua_rawsetfield(L, -2, "__type");
		}
		lua_setmetatable(L, -2);

		propHolder->prop = prop;
		return 1;
	}

	int ClassFindMethod(lua_State* L) {
		ClassHolder* cls = (ClassHolder*) lua_touserdata(L, 1);
		if(!lua_isstring(L, 2)) {
			std::println("[ERR] [LUAU] Class:findproperty(name) name must be a string");
			return 0;
		}

		std::string name = luaL_checkstring(L, 2);

		const MethodBase* meth = cls->cls->findMethod(name);
		if(meth == nullptr) {
			lua_pushnil(L);
			return 1;
		}

		MethodHolder* methHolder = static_cast<MethodHolder*>(lua_newuserdata(L, sizeof(MethodHolder)));
		if(luaL_newmetatable(L, "Method")) {
			luaL_register(L, nullptr, methodMeth);
			lua_pushliteral(L, "Method");
			lua_rawsetfield(L, -2, "__type");
		}
		lua_setmetatable(L, -2);

		methHolder->meth = meth;
		return 1;
	}

	int ClassFindEventHandler(lua_State* L) {
		ClassHolder* cls = static_cast<ClassHolder*>(lua_touserdata(L, 1));
		ClassHolder* evtClass = static_cast<ClassHolder*>(luaL_checkudata(L, 2, "Class"));

		const EventHandlerBase* toWrap = cls->cls->findEventHandler(evtClass->cls);
		if(toWrap == nullptr) {
			lua_pushnil(L);
			return 1;
		}

		EventHandlerHolder* evtHolder = static_cast<EventHandlerHolder*>(lua_newuserdata(L, sizeof(EventHandlerHolder)));
		if(luaL_newmetatable(L, "EventHandler")) {
			luaL_register(L, nullptr, eventHandlerMeth);
			lua_pushliteral(L, "EventHandler");
			lua_rawsetfield(L, -2, "__type");
		}
		lua_setmetatable(L, -2);

		evtHolder->handler = toWrap;
		return 1;
	}

	int ClassIsAbstract(lua_State* L) {
		ClassHolder* cls = (ClassHolder*) lua_touserdata(L, 1);
		lua_pushboolean(L, cls->cls->isAbstract());
		return 1;
	}

	int ClassInstanceOf(lua_State* L) {
		if(!lua_isuserdata(L, 2)) {
			std::println("[ERR] [LUAU] Expected type 'Class', got {}", lua_typename(L, lua_type(L, 2)));
			lua_pushboolean(L, false);
			return 1;
		}

		ClassHolder* cls = (ClassHolder*) lua_touserdata(L, 1);
		ClassHolder* parent = (ClassHolder*) luaL_checkudata(L, 2, "Class");

		lua_pushboolean(L, cls->cls->instanceOf(parent->cls));
		return 1;
	}

	int ClassCreate(lua_State* L) {
		ClassHolder* clsHolder = (ClassHolder*) lua_touserdata(L, 1);
		const Class* cls = clsHolder->cls;

		if(cls == nullptr) return 0;
		if(cls->isAbstract()) return 0;
		
		ObjectHolder* ptr = static_cast<ObjectHolder*>(lua_newuserdatadtor(L, sizeof(ObjectHolder), [](void* ptr) {
			ObjectHolder* self = static_cast<ObjectHolder*>(ptr);
			self->obj.~shared_ptr<Object>();
		}));

		if(luaL_newmetatable(L, "Object")) {
			luaL_register(L, nullptr, objectMeth);
			lua_pushliteral(L, "Object");
			lua_rawsetfield(L, -2, "__type");
		}
		lua_setmetatable(L, -2);

		new(&ptr->obj) std::shared_ptr<Object>(cls->constructor->create());

		return 1;
	}
}
