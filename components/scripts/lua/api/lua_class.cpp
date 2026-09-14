#include "api/lua_function.hpp"
#include "api/lua_property.hpp"
#include "api/lua_event_handler.hpp"
#include "ve/class_db.hpp"
#include <api/lua_class.hpp>
#include <api/lua_constructor.hpp>

#include <ve/object.hpp>

#include <print>
#include <vector>

extern "C" {
#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>
}

namespace VoidEngine::Scripts::Lua::API {
	LuaClassWrapper* lua_pushclasswrapper(lua_State* state) {
		LuaClassWrapper* cls = static_cast<LuaClassWrapper*>(lua_newuserdata(state, sizeof(LuaClassWrapper)));
		luaL_getmetatable(state, "Class");
		lua_setmetatable(state, -2);
		return cls;
	}

	int lua_ClassNew(lua_State* state) {
		if(!lua_isstring(state, 1)) {
			lua_pushstring(state, "Arg 0 of Class.new must be a string");
			lua_error(state);
			return 0;
		}

		LuaClassWrapper* super = static_cast<LuaClassWrapper*>(luaL_checkudata(state, 2, "Class"));

		LuaClassWrapper* cls = lua_pushclasswrapper(state);

		cls->cls = new Class;
		const_cast<Class*>(cls->cls)->name = luaL_checkstring(state, 1);
		const_cast<Class*>(cls->cls)->super = super->cls;
		return 1;
	}

	int lua_ClassGet(lua_State* state) {
		if(!lua_isstring(state, 1)) {
			lua_pushstring(state, "Arg 0 of Class.get must be a string");
			lua_error(state);
			return 0;
		}

		LuaClassWrapper* cls = static_cast<LuaClassWrapper*>(lua_newuserdata(state, sizeof(LuaClassWrapper)));
		luaL_getmetatable(state, "Class");
		lua_setmetatable(state, -2);

		std::string clsName = luaL_checkstring(state, 1);

		cls->cls = ClassDB::getInstance()->getClassByName(clsName);
		return 1;
	}

	int lua_ClassRegister(lua_State* state) {
		LuaClassWrapper* cls = static_cast<LuaClassWrapper*>(luaL_checkudata(state, 1, "Class"));
		ClassDB::getInstance()->registerClass(cls->cls);
		return 0;
	}

	int lua_ClassIsAbstract(lua_State* state) {
		LuaClassWrapper* cls = static_cast<LuaClassWrapper*>(luaL_checkudata(state, 1, "Class"));
		lua_pushboolean(state, cls->cls->isAbstract());
		return 1;
	}
	
	int lua_ClassSetConstructor(lua_State* state) {
		LuaClassWrapper* cls = static_cast<LuaClassWrapper*>(luaL_checkudata(state, 1, "Class"));
		LuaConstructorWrapper* ctor = static_cast<LuaConstructorWrapper*>(luaL_checkudata(state, 2, "Constructor"));
		const_cast<LuaConstructor*>(static_cast<const LuaConstructor*>(ctor->ctor))->cls = cls->cls;
		const_cast<Class*>(cls->cls)->constructor = ctor->ctor;
		return 0;
	}

	int lua_ClassGetConstructor(lua_State* state) {
		LuaClassWrapper* cls = static_cast<LuaClassWrapper*>(luaL_checkudata(state, 1, "Class"));
		if(cls->cls->constructor == nullptr) {
			lua_pushnil(state);
			return 1;
		}

		LuaConstructorWrapper* wrapper = static_cast<LuaConstructorWrapper*>(lua_newuserdata(state, sizeof(LuaConstructorWrapper)));
		wrapper->ctor = cls->cls->constructor;

		luaL_getmetatable(state, "Constructor");
		lua_setmetatable(state, -2);
		
		return 1;
	}

	int lua_ClassInstanceOf(lua_State* state) {
		LuaClassWrapper* cls = static_cast<LuaClassWrapper*>(luaL_checkudata(state, 1, "Class"));
		LuaClassWrapper* other = static_cast<LuaClassWrapper*>(luaL_checkudata(state, 2, "Class"));
		lua_pushboolean(state, cls->cls->instanceOf(other->cls));
		return 1;
	}

	int lua_ClassGetSuper(lua_State* state) {
		LuaClassWrapper* cls = static_cast<LuaClassWrapper*>(luaL_checkudata(state, 1, "Class"));
		LuaClassWrapper* super = static_cast<LuaClassWrapper*>(lua_newuserdata(state, sizeof(LuaClassWrapper)));
		super->cls = cls->cls->getSuper();
		luaL_getmetatable(state, "Class");
		lua_setmetatable(state, -2);
		return 1;
	}

	int lua_ClassGetName(lua_State* state) {
		LuaClassWrapper* cls = static_cast<LuaClassWrapper*>(luaL_checkudata(state, 1, "Class"));
		lua_pushstring(state, cls->cls->getName());
		return 1;
	}

	int lua_ClassAddFunction(lua_State* state) {
		LuaClassWrapper* self = static_cast<LuaClassWrapper*>(luaL_checkudata(state, 1, "Class"));
		LuaFunctionWrapper* function = static_cast<LuaFunctionWrapper*>(luaL_checkudata(state, 2, "Function"));

		auto methods = const_cast<std::vector<const MethodBase*>*>(&self->cls->methods);
		methods->push_back(function->method);
		return 0;
	}

	int lua_ClassAddProperty(lua_State* state) {
		LuaClassWrapper* self = static_cast<LuaClassWrapper*>(luaL_checkudata(state, 1, "Class"));
		LuaPropertyWrapper* property = static_cast<LuaPropertyWrapper*>(luaL_checkudata(state, 2, "Property"));

		auto properties = const_cast<std::vector<const PropertyBase*>*>(&self->cls->properties);
		properties->push_back(property->property);
		return 0;
	}

	int lua_ClassAddEventHandler(lua_State* state) {
		LuaClassWrapper* self = static_cast<LuaClassWrapper*>(luaL_checkudata(state, 1, "Class"));
		LuaEventHandlerWrapper* handler = static_cast<LuaEventHandlerWrapper*>(
			luaL_checkudata(state, 2, "EventHandler")
		);

		auto handlers = const_cast<std::vector<const EventHandlerBase*>*>(&self->cls->eventHandlers);
		handlers->push_back(handler->handler);
		return 0;
	}

	int lua_ClassGetProperties(lua_State* state) {
		LuaClassWrapper* self = static_cast<LuaClassWrapper*>(luaL_checkudata(state, 1, "Class"));
		auto props = self->cls->getProperties();

		lua_createtable(state, props.size(), 0);
		// TODO: add all properties to the array
		return 1;
	}

	int lua_ClassGetFunctions(lua_State* state) {
		LuaClassWrapper* self = static_cast<LuaClassWrapper*>(luaL_checkudata(state, 1, "Class"));
		auto funcs = self->cls->getMethods();

		lua_createtable(state, funcs.size(), 0);
		for(size_t idx = 0; idx < funcs.size(); idx++) {
			LuaFunctionWrapper* funcWrapper = lua_pushfunctionwrapper(state);
			funcWrapper->method = funcs[idx];
			lua_rawseti(state, -2, idx + 1);
		}
		return 1;
	}

	int lua_ClassGetEventHandlers(lua_State* state) {
		LuaClassWrapper* self = static_cast<LuaClassWrapper*>(luaL_checkudata(state, 1, "Class"));
		auto handlers = self->cls->getEventHandlers();

		lua_createtable(state, handlers.size(), 0);
		// TODO: add all handlers to the array
		return 1;
	}

	int lua_ClassFindProperty(lua_State* state) {
		LuaClassWrapper* self = static_cast<LuaClassWrapper*>(luaL_checkudata(state, 1, "Class"));
		std::string name = luaL_checkstring(state, 2);

		const auto prop = self->cls->findProperty(name);
		if(prop == nullptr) {
			lua_pushnil(state);
			return 1;
		}

		LuaPropertyWrapper* wrapper = lua_pushpropertywrapper(state);
		wrapper->property = prop;
		return 1;
	}

	int lua_ClassFindFunction(lua_State* state) {
		LuaClassWrapper* self = static_cast<LuaClassWrapper*>(luaL_checkudata(state, 1, "Class"));
		std::string name = luaL_checkstring(state, 2);

		const auto func = self->cls->findMethod(name);
		if(func == nullptr) {
			lua_pushnil(state);
			return 1;
		}

		LuaFunctionWrapper* wrapper = lua_pushfunctionwrapper(state);
		wrapper->method = func;
		return 1;
	}

	int lua_ClassFindEventHandler(lua_State* state) {
		LuaClassWrapper* self = static_cast<LuaClassWrapper*>(luaL_checkudata(state, 1, "Class"));
		LuaClassWrapper* evtCls = static_cast<LuaClassWrapper*>(luaL_checkudata(state, 2, "Class"));

		const auto handler = self->cls->findEventHandler(evtCls->cls);
		if(handler == nullptr) {
			lua_pushnil(state);
			return 1;
		}

		// TODO: push the handler
		lua_pushnil(state);
		return 1;
	}

	int lua_Class__index(lua_State* state) {
		LuaClassWrapper* cls = static_cast<LuaClassWrapper*>(luaL_checkudata(state, 1, "Class"));

		std::string idxName = lua_tostring(state, 2);
		lua_getmetatable(state, 1);
		lua_getfield(state, -1, idxName.c_str());
		return 1;
	}

	int lua_Class__tostring(lua_State* state) {
		LuaClassWrapper* cls = static_cast<LuaClassWrapper*>(luaL_testudata(state, 1, "Class"));
		if(cls == nullptr) {
			lua_pushstring(state, "how?");
			lua_error(state);
			return 0;
		}

		lua_pushstring(state, std::format("Class: {}", cls->cls->getName()).c_str());
		return 1;
	}

	int lua_Class__eq(lua_State* state) {
		LuaClassWrapper* RHS = static_cast<LuaClassWrapper*>(luaL_testudata(state, 2, "Class"));
		if(RHS == nullptr) {
			lua_pushboolean(state, false);
			return 1;
		}

		LuaClassWrapper* LHS = static_cast<LuaClassWrapper*>(luaL_testudata(state, 1, "Class"));
		if(LHS == nullptr) {
			lua_pushboolean(state, false);
			return 1;
		}

		lua_pushboolean(state, LHS->cls == RHS->cls);
		return 1;
	}

	int luaopen_Class(lua_State* state) {
		luaL_newmetatable(state, "Class");
		luaL_setfuncs(state, classLib, 0);
		lua_setglobal(state, "Class");
		return 0;
	}
}