#include <api/lua_property.hpp>
#include <memory>
#include <print>

#include "api/lua_object_script.hpp"
#include "lua_script_engine.hpp"
#include "ve/class_db.hpp"

extern "C" {
#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>
}

namespace VoidEngine::Scripts::Lua::API {
	LuaProperty::LuaProperty(std::string name, int getIdx, int setIdx) : PropertyBase(name) {
		auto state = LuaScriptEngine::getInstance()->state;

		lua_pushlightuserdata(state, this);
		lua_pushvalue(state, getIdx);
		lua_settable(state, LUA_REGISTRYINDEX);

		if(setIdx != 0) {
			lua_pushlightuserdata(state, this + SETTER_OFFSET);
			lua_pushvalue(state, setIdx);
			lua_settable(state, LUA_REGISTRYINDEX);
		}
	}

	Variant LuaProperty::get(std::shared_ptr<Object> object) const {
		if(object->getScript() == nullptr) {
			std::println("[ERR] [Lua] Cannot get property {} from object, missing lua script", getName());
			return nullptr;
		}

		if(object->getScript()->getScriptEngine()->getLanguage() != "lua") {
			std::println(
				"[ERR] [Lua] Cannot get property {} from object, script languge is not lua (got {})", getName(),
				object->getScript()->getScriptEngine()->getLanguage()
			);
			return nullptr;
		}

		auto state = LuaScriptEngine::getInstance()->state;
		auto script = std::static_pointer_cast<LuaObjectScript>(object->getScript());
		lua_pushlightuserdata(state, const_cast<LuaProperty*>(this));
		lua_gettable(state, LUA_REGISTRYINDEX);
		if(lua_type(state, -1) != LUA_TFUNCTION) {
			std::println("[ERR] [Lua] getter for {} is not a function", getName());
			return nullptr;
		}

		script->pushObject(state);
		if(lua_pcall(state, 1, 1, 0) != 0) {
			std::string err = luaL_checkstring(state, -1);
			std::println("[ERR] [Lua] {}", err);
			return nullptr;
		}

		int top = -1;
		return LuaScriptEngine::getInstance()->objectToVariant(&top);
	}

	void LuaProperty::set(std::shared_ptr<Object> object, Variant value) const {
		if(object->getScript() == nullptr) {
			std::println("[ERR] [Lua] Cannot get property {} from object, missing lua script", getName());
			return;
		}

		if(object->getScript()->getScriptEngine()->getLanguage() != "lua") {
			std::println(
				"[ERR] [Lua] Cannot get property {} from object, script languge is not lua (got {})", getName(),
				object->getScript()->getScriptEngine()->getLanguage()
			);
			return;
		}

		auto state = LuaScriptEngine::getInstance()->state;
		auto script = std::static_pointer_cast<LuaObjectScript>(object->getScript());
		lua_pushlightuserdata(state, const_cast<LuaProperty*>(this) + SETTER_OFFSET);
		lua_gettable(state, LUA_REGISTRYINDEX);
		if(lua_type(state, -1) != LUA_TFUNCTION) {
			std::println("[ERR] [Lua] getter for {} is not a function", getName());
			return;
		}

		script->pushObject(state);

		LuaScriptEngine::getInstance()->objectFromVariant(value);

		if(lua_pcall(state, 2, 0, 0) != 0) {
			std::string err = luaL_checkstring(state, -1);
			std::println("[ERR] [Lua] {}", err);
		}
	}

	bool LuaProperty::isReadOnly() const {
		auto state = LuaScriptEngine::getInstance()->state;
		
		lua_pushlightuserdata(state, const_cast<LuaProperty*>(this) + SETTER_OFFSET);
		lua_gettable(state, LUA_REGISTRYINDEX);
		bool readOnly = lua_type(state, -1) == LUA_TNIL;
		lua_pop(state, 1);
		return readOnly;
	}

	LuaPropertyWrapper* lua_pushpropertywrapper(lua_State* state) {
		LuaPropertyWrapper* property = static_cast<LuaPropertyWrapper*>(lua_newuserdata(state, sizeof(LuaPropertyWrapper)));
		luaL_getmetatable(state, "Property");
		lua_setmetatable(state, -2);
		return property;
	}

	int lua_PropertyNew(lua_State* state) {
		const std::string name = luaL_checkstring(state, 1);
		luaL_checktype(state, 2, LUA_TFUNCTION);

		bool hasSetter = lua_gettop(state) >= 3;
		if(hasSetter) {
			luaL_checktype(state, 3, LUA_TFUNCTION);
		}

		LuaPropertyWrapper* property = lua_pushpropertywrapper(state);
		property->property = new LuaProperty(name, 2, hasSetter ? 0 : 3);

		return 1;
	}

	int lua_Property__index(lua_State* state) {
		LuaPropertyWrapper* prop = static_cast<LuaPropertyWrapper*>(luaL_checkudata(state, 1, "Property"));

		std::string idxName = lua_tostring(state, 2);
		lua_getmetatable(state, 1);
		lua_getfield(state, -1, idxName.c_str());
		return 1;
	}

	int lua_Property__tostring(lua_State* state) {
		LuaPropertyWrapper* prop = static_cast<LuaPropertyWrapper*>(luaL_checkudata(state, 1, "Property"));
		lua_pushstring(state, prop->property->getName().c_str());
		return 1;
	}

	int lua_Property__eq(lua_State* state) {
		LuaPropertyWrapper* LHS = static_cast<LuaPropertyWrapper*>(luaL_checkudata(state, 1, "Property"));
		LuaPropertyWrapper* RHS = static_cast<LuaPropertyWrapper*>(luaL_checkudata(state, 1, "Property"));
		lua_pushboolean(state, LHS->property == RHS->property);
		return 1;
	}

	int lua_PropertyGetName(lua_State* state) {
		LuaPropertyWrapper* prop = static_cast<LuaPropertyWrapper*>(luaL_checkudata(state, 1, "Property"));
		lua_pushstring(state, prop->property->getName().c_str());
		return 1;
	}

	int lua_PropertyIsReadOnly(lua_State* state) {
		LuaPropertyWrapper* prop = static_cast<LuaPropertyWrapper*>(luaL_checkudata(state, 1, "Property"));
		lua_pushboolean(state, prop->property->isReadOnly());
		return 1;
	}

	int luaopen_Property(lua_State* state) {
		luaL_newmetatable(state, "Property");
		luaL_setfuncs(state, propertyLib, 0);
		lua_setglobal(state, "Property");
		return 0;
	}
}
