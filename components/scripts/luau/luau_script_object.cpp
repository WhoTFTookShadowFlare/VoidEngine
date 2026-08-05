#include "luau_script_object.hpp"
#include "lua.h"
#include "lualib.h"
#include "luau_script_engine.hpp"
#include "ve/script/a_script_object.hpp"
#include "ve/variant.hpp"
#include <algorithm>
#include <cassert>
#include <cstdint>
#include <print>
#include <string>
#include <vector>

namespace VoidEngine::Scripts::Luau {
	const Class LuauScriptObject::ClassData = {
		.name = "LuauScriptObject",
		.super = &AScriptObject::ClassData
	};

	LuauScriptObject::LuauScriptObject() {
		auto L = LuauScriptEngine::getInstance()->vmState;
		assert(lua_gettop(L) > 0);

		lua_pushlightuserdata(L, this);
		lua_pushvalue(L, -2);
		lua_settable(L, LUA_REGISTRYINDEX);
	}

	LuauScriptObject::~LuauScriptObject() {
		auto L = LuauScriptEngine::getInstance()->vmState;
		lua_pushlightuserdata(L, this);
		lua_pushnil(L);
		lua_settable(L, LUA_REGISTRYINDEX);
	}

	std::shared_ptr<AScriptEngine> LuauScriptObject::getScriptEngine() {
		return LuauScriptEngine::getInstance();
	}

	Variant LuauScriptObject::call(std::string fnName, std::vector<Variant> args) {
		auto engine = LuauScriptEngine::getInstance();
		auto L = engine->vmState;
		lua_pushlightuserdata(L, this);
		lua_gettable(L, LUA_REGISTRYINDEX);
		assert(lua_type(L, -1) == LUA_TTABLE);

		lua_getfield(L, -1, fnName.c_str());
		if(!lua_isfunction(L, -1)) {
			std::println("Cannot call a value of type: {}", lua_typename(L, lua_type(L, -1)));
			lua_pop(L, 2);
			return nullptr;
		}

		lua_pushvalue(L, -2);
		std::for_each(args.cbegin(), args.cend(), [&engine](const auto& arg) {
			engine->objectFromVariant(arg);
		});
		lua_pcall(L, args.size() + 1, 1, 0);

		uint32_t *top = new uint32_t(lua_gettop(L));
		Variant retVal = engine->objectToVariant(top);
		delete top;

		lua_pop(L, 2);
		return retVal;
	}

	Variant LuauScriptObject::get(std::string name) {
		auto engine = LuauScriptEngine::getInstance();
		auto L = engine->vmState;
		lua_pushlightuserdata(L, this);
		lua_gettable(L, LUA_REGISTRYINDEX);
		assert(lua_type(L, -1) == LUA_TTABLE);

		lua_getfield(L, -1, name.c_str());

		uint32_t *top = new uint32_t(lua_gettop(L));
		Variant retVal = engine->objectToVariant(top);
		delete top;

		lua_pop(L, 1);
		return retVal;
	}

	void LuauScriptObject::set(std::string name, Variant value) {
		auto engine = LuauScriptEngine::getInstance();
		auto L = engine->vmState;
		lua_pushlightuserdata(L, this);
		lua_gettable(L, LUA_REGISTRYINDEX);
		assert(lua_type(L, -1) == LUA_TTABLE);

		lua_pushstring(L, name.c_str());
		engine->objectFromVariant(value);
		lua_settable(L, -3);

		lua_pop(L, 1);
	}

	std::vector<std::string> LuauScriptObject::getFunctions() {
		auto* L = LuauScriptEngine::getInstance()->vmState;
		lua_pushlightuserdata(L, this);
		lua_gettable(L, LUA_REGISTRYINDEX);
		assert(lua_type(L, -1) == LUA_TTABLE);

		std::vector<std::string> funcs;
		lua_pushnil(L);
		while(lua_next(L, -2)) {
			if(lua_type(L, -2) != LUA_TSTRING) {
				lua_pop(L, 1);
				continue;
			}
			if(lua_type(L, -1) == LUA_TFUNCTION)
				funcs.push_back(luaL_checkstring(L, -2));
			lua_pop(L, 1);
		}

		lua_pop(L, 1);
		return funcs;
	}

	std::vector<std::string> LuauScriptObject::getProperties() {
		auto* L = LuauScriptEngine::getInstance()->vmState;
		lua_pushlightuserdata(L, this);
		lua_gettable(L, LUA_REGISTRYINDEX);
		assert(lua_type(L, -1) == LUA_TTABLE);

		std::vector<std::string> props;
		lua_pushnil(L);
		while(lua_next(L, -2)) {
			if(lua_type(L, -2) != LUA_TSTRING) {
				lua_pop(L, 1);
				continue;
			}
			if(lua_type(L, -1) != LUA_TFUNCTION)
				props.push_back(luaL_checkstring(L, -2));
			lua_pop(L, 1);
		}

		lua_pop(L, 1);
		return props;
	}
}
