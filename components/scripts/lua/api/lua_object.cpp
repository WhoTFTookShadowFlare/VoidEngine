#include "api/lua_function.hpp"
#include "api/lua_property.hpp"
#include "lua_script_engine.hpp"
#include <api/lua_object.hpp>
#include <format>

extern "C" {
#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>
}

namespace VoidEngine::Scripts::Lua::API {
	LuaObjectWrapper* lua_pushObjectWrapper(lua_State* state) {
		LuaObjectWrapper* object = static_cast<LuaObjectWrapper*>(lua_newuserdata(state, sizeof(LuaObjectWrapper)));
		luaL_getmetatable(state, "Object");
		lua_setmetatable(state, -2);
		new (object) LuaObjectWrapper;
		return object;
	}

	int lua_Object__index(lua_State* state) {
		LuaObjectWrapper* object = static_cast<LuaObjectWrapper*>(luaL_checkudata(state, 1, "Object"));
		std::string propName = luaL_checkstring(state, 2);

		const auto function = object->object->getClass()->findMethod(propName);
		if(function == nullptr) {
			const auto property = object->object->getClass()->findProperty(propName);
			if(property == nullptr) {
				lua_pushstring(state, std::format(
					"No method or property with name {} on class {}", propName,
					object->object->getClass()->getName()
				).c_str());
				lua_error(state);
				return 1;
			}

			LuaScriptEngine::getInstance()->objectFromVariant(property->get(object->object));
			return 1;
		}

		LuaFunctionWrapper* funcWrapper = lua_pushfunctionwrapper(state);
		funcWrapper->method = function;
		return 1;
	}

	int lua_Object__newindex(lua_State* state) {
		LuaObjectWrapper* object = static_cast<LuaObjectWrapper*>(luaL_checkudata(state, 1, "Object"));
		std::string propName = luaL_checkstring(state, 2);
		
		const auto property = object->object->getClass()->findProperty(propName);
		if(property == nullptr) {
			lua_pushstring(state, std::format("No property with name {}", propName).c_str());
			lua_error(state);
			return 1;
		}

		if(property->isReadOnly()) {
			lua_pushstring(state, std::format("Property {} is readonly", propName).c_str());
			lua_error(state);
			return 1;
		}

		int value = 3;
		property->set(object->object, LuaScriptEngine::getInstance()->objectToVariant(&value));
		return 0;
	}

	int lua_Object__tostring(lua_State* state) {
		LuaObjectWrapper* object = static_cast<LuaObjectWrapper*>(luaL_checkudata(state, 1, "Object"));
		lua_pushstring(state, std::format("Object ({})", object->object->getClass()->getName()).c_str());
		return 1;
	}

	int lua_Object__eq(lua_State* state) {
		LuaObjectWrapper* LHS = static_cast<LuaObjectWrapper*>(luaL_checkudata(state, 1, "Object"));
		LuaObjectWrapper* RHS = static_cast<LuaObjectWrapper*>(luaL_checkudata(state, 2, "Object"));
		lua_pushboolean(state, LHS->object == RHS->object);
		return 1;
	}

	int lua_Object__gc(lua_State* state) {
		LuaObjectWrapper* object = static_cast<LuaObjectWrapper*>(luaL_checkudata(state, 1, "Object"));
		//object->object = nullptr; // TODO: properly delete the object
		return 0;
	}

	int luaopen_Object(lua_State* state) {
		luaL_newmetatable(state, "Object");
		luaL_setfuncs(state, objectLib, 0);
		lua_setglobal(state, "Object");
		return 0;
	}
}
