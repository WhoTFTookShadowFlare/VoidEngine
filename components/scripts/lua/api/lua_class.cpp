#include "api/lua_function.hpp"
#include "api/lua_property.hpp"
#include "api/lua_event_handler.hpp"
#include "ve/class_db.hpp"
#include <api/lua_class.hpp>
#include <api/lua_constructor.hpp>
#include <api/lua_object.hpp>

#include <ve/object.hpp>

#include <print>
#include <vector>

extern "C" {
#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>
}

namespace VoidEngine::Scripts::Lua::API {
	LuaClassWrapper* lua_pushClassWrapper(lua_State* state) {
		LuaClassWrapper* cls = static_cast<LuaClassWrapper*>(lua_newuserdata(state, sizeof(LuaClassWrapper)));
		luaL_getmetatable(state, "Class");
		lua_setmetatable(state, -2);
		return cls;
	}

	LuaClassWrapper* lua_checkClass(lua_State* state, int idx) {
		return static_cast<LuaClassWrapper*>(luaL_checkudata(state, idx, "Class"));
	}

	int lua_ClassNew(lua_State* state) {
		LuaClassWrapper* super = lua_checkClass(state, 2);

		LuaClassWrapper* cls = lua_pushClassWrapper(state);

		cls->cls = new Class;
		const_cast<Class*>(cls->cls)->name = luaL_checkstring(state, 1);
		const_cast<Class*>(cls->cls)->super = super->cls;
		return 1;
	}

	int lua_ClassGet(lua_State* state) {
		std::string clsName = luaL_checkstring(state, 1);
		LuaClassWrapper* cls = lua_pushClassWrapper(state);

		cls->cls = ClassDB::getInstance()->getClassByName(clsName);
		return 1;
	}

	int lua_ClassRegister(lua_State* state) {
		LuaClassWrapper* cls = static_cast<LuaClassWrapper*>(luaL_checkudata(state, 1, "Class"));
		ClassDB::getInstance()->registerClass(cls->cls);
		return 0;
	}

	int lua_ClassCreate(lua_State* state) {
		LuaClassWrapper* cls = lua_checkClass(state, 1);

		LuaObjectWrapper* object = lua_pushObjectWrapper(state);
		object->object = cls->cls->constructor->create();
		return 1;
	}

	int lua_ClassIsAbstract(lua_State* state) {
		LuaClassWrapper* cls = lua_checkClass(state, 1);
		lua_pushboolean(state, cls->cls->isAbstract());
		return 1;
	}
	
	int lua_ClassSetConstructor(lua_State* state) {
		LuaClassWrapper* cls = lua_checkClass(state, 1);
		LuaConstructorWrapper* ctor = lua_checkConstructor(state, 2);
		const_cast<LuaConstructor*>(static_cast<const LuaConstructor*>(ctor->ctor))->cls = cls->cls;
		const_cast<Class*>(cls->cls)->constructor = ctor->ctor;
		return 0;
	}

	int lua_ClassGetConstructor(lua_State* state) {
		LuaClassWrapper* cls = lua_checkClass(state, 1);
		if(cls->cls->constructor == nullptr) {
			lua_pushnil(state);
			return 1;
		}

		LuaConstructorWrapper* wrapper = lua_pushConstructorWrapper(state);
		wrapper->ctor = cls->cls->constructor;

		luaL_getmetatable(state, "Constructor");
		lua_setmetatable(state, -2);
		
		return 1;
	}

	int lua_ClassInstanceOf(lua_State* state) {
		LuaClassWrapper* cls = lua_checkClass(state, 1);
		LuaClassWrapper* other = lua_checkClass(state, 2);
		lua_pushboolean(state, cls->cls->instanceOf(other->cls));
		return 1;
	}

	int lua_ClassGetSuper(lua_State* state) {
		LuaClassWrapper* cls = lua_checkClass(state, 1);
		LuaClassWrapper* super = lua_pushClassWrapper(state);
		super->cls = cls->cls->getSuper();
		luaL_getmetatable(state, "Class");
		lua_setmetatable(state, -2);
		return 1;
	}

	int lua_ClassGetName(lua_State* state) {
		LuaClassWrapper* cls = lua_checkClass(state, 1);
		lua_pushstring(state, cls->cls->getName());
		return 1;
	}

	int lua_ClassAddFunction(lua_State* state) {
		LuaClassWrapper* self = lua_checkClass(state, 1);
		LuaFunctionWrapper* function = static_cast<LuaFunctionWrapper*>(luaL_checkudata(state, 2, "Function"));

		auto methods = const_cast<std::vector<const MethodBase*>*>(&self->cls->methods);
		methods->push_back(function->method);
		return 0;
	}

	int lua_ClassAddProperty(lua_State* state) {
		LuaClassWrapper* self = lua_checkClass(state, 1);
		LuaPropertyWrapper* property = lua_checkProperty(state, 2);

		auto properties = const_cast<std::vector<const PropertyBase*>*>(&self->cls->properties);
		properties->push_back(property->property);
		return 0;
	}

	int lua_ClassAddEventHandler(lua_State* state) {
		LuaClassWrapper* self = lua_checkClass(state, 1);
		LuaEventHandlerWrapper* handler = static_cast<LuaEventHandlerWrapper*>(
			luaL_checkudata(state, 2, "EventHandler")
		);

		auto handlers = const_cast<std::vector<const EventHandlerBase*>*>(&self->cls->eventHandlers);
		handlers->push_back(handler->handler);
		return 0;
	}

	int lua_ClassGetProperties(lua_State* state) {
		LuaClassWrapper* self = lua_checkClass(state, 1);
		auto props = self->cls->getProperties();

		lua_createtable(state, props.size(), 0);
		for(size_t idx = 0; idx < props.size(); idx++) {
			LuaPropertyWrapper* wrapper = lua_pushPropertyWrapper(state);
			wrapper->property = props[idx];
			lua_rawseti(state, -2, idx + 1);
		}
		return 1;
	}

	int lua_ClassGetFunctions(lua_State* state) {
		LuaClassWrapper* self = lua_checkClass(state, 1);
		auto funcs = self->cls->getMethods();

		lua_createtable(state, funcs.size(), 0);
		for(size_t idx = 0; idx < funcs.size(); idx++) {
			LuaFunctionWrapper* funcWrapper = lua_pushFunctionWrapper(state);
			funcWrapper->method = funcs[idx];
			lua_rawseti(state, -2, idx + 1);
		}
		return 1;
	}

	int lua_ClassGetEventHandlers(lua_State* state) {
		LuaClassWrapper* self = lua_checkClass(state, 1);
		auto handlers = self->cls->getEventHandlers();

		lua_createtable(state, handlers.size(), 0);
		for(size_t idx = 0; idx < handlers.size(); idx++) {
			LuaEventHandlerWrapper* wrapper = lua_pushEventHandlerWrapper(state);
			wrapper->handler = handlers[idx];
			lua_rawseti(state, -2, idx + 1);
		}
		return 1;
	}

	int lua_ClassFindProperty(lua_State* state) {
		LuaClassWrapper* self = lua_checkClass(state, 1);
		std::string name = luaL_checkstring(state, 2);

		const auto prop = self->cls->findProperty(name);
		if(prop == nullptr) {
			lua_pushnil(state);
			return 1;
		}

		LuaPropertyWrapper* wrapper = lua_pushPropertyWrapper(state);
		wrapper->property = prop;
		return 1;
	}

	int lua_ClassFindFunction(lua_State* state) {
		LuaClassWrapper* self = lua_checkClass(state, 1);
		std::string name = luaL_checkstring(state, 2);

		const auto func = self->cls->findMethod(name);
		if(func == nullptr) {
			lua_pushnil(state);
			return 1;
		}

		LuaFunctionWrapper* wrapper = lua_pushFunctionWrapper(state);
		wrapper->method = func;
		return 1;
	}

	int lua_ClassFindEventHandler(lua_State* state) {
		LuaClassWrapper* self = lua_checkClass(state, 1);
		LuaClassWrapper* evtCls = lua_checkClass(state, 2);

		const auto handler = self->cls->findEventHandler(evtCls->cls);
		if(handler == nullptr) {
			lua_pushnil(state);
			return 1;
		}

		LuaEventHandlerWrapper* wrapper = lua_pushEventHandlerWrapper(state);
		wrapper->handler = handler;
		return 1;
	}

	int lua_Class__index(lua_State* state) {
		LuaClassWrapper* cls = lua_checkClass(state, 1);

		std::string idxName = lua_tostring(state, 2);
		lua_getmetatable(state, 1);
		lua_getfield(state, -1, idxName.c_str());
		return 1;
	}

	int lua_Class__tostring(lua_State* state) {
		LuaClassWrapper* cls = lua_checkClass(state, 1);
		lua_pushstring(state, std::format("Class: {}", cls->cls->getName()).c_str());
		return 1;
	}

	int lua_Class__eq(lua_State* state) {
		LuaClassWrapper* LHS = lua_checkClass(state, 1);
		LuaClassWrapper* RHS = lua_checkClass(state, 2);
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