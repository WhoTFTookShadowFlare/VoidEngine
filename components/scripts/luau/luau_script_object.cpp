#include "luau_script_object.hpp"
#include "lua.h"
#include "lualib.h"
#include "luau_script_engine.hpp"
#include "types/class_holder.hpp"
#include "ve/class_db.hpp"
#include "ve/script/a_script_object.hpp"
#include "ve/variant.hpp"
#include <algorithm>
#include <cassert>
#include <cstdint>
#include <print>
#include <string>
#include <vector>

namespace VoidEngine::Scripts::Luau {
	LuauObjectScript::LuauObjectScript() {
		auto L = LuauScriptEngine::getInstance()->vmState;
		assert(lua_gettop(L) > 0);

		lua_pushlightuserdata(L, this);
		lua_pushvalue(L, -2);
		lua_settable(L, LUA_REGISTRYINDEX);
	}

	LuauObjectScript::~LuauObjectScript() {
		auto L = LuauScriptEngine::getInstance()->vmState;
		lua_pushlightuserdata(L, this);
		lua_pushnil(L);
		lua_settable(L, LUA_REGISTRYINDEX);
	}

	std::shared_ptr<AScriptEngine> LuauObjectScript::getScriptEngine() {
		return LuauScriptEngine::getInstance();
	}

	const Class* LuauObjectScript::getClass() {
		auto L = LuauScriptEngine::getInstance()->vmState;
		lua_pushlightuserdata(L, this);
		lua_gettable(L, LUA_REGISTRYINDEX);

		lua_pushstring(L, "getClass");
		lua_gettable(L, -2);

		lua_pcall(L, 0, 1, 0);

		const Class* cls = nullptr;
		if(lua_isstring(L, -1)) {
			cls = ClassDB::getInstance()->getClassByName(luaL_checkstring(L, -1));
		} else if(lua_isuserdata(L, -1)) {
			void* ptr = lua_touserdata(L, -1);
			if(ptr != nullptr) {
				if(lua_getmetatable(L, -1)) {
					lua_getfield(L, -1, "__type");
					std::string type = luaL_checkstring(L, -1);
					lua_pop(L, 2);

					if(type == "Class") {
						cls = static_cast<ClassHolder*>(lua_touserdata(L, -1))->cls;
					}
				}
			}
		}

		return cls;
	}

	Variant LuauObjectScript::call(std::string fnName, std::vector<Variant> args) {
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

	Variant LuauObjectScript::get(std::string name) {
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

	void LuauObjectScript::set(std::string name, Variant value) {
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

	std::vector<std::string> LuauObjectScript::getFunctions() {
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

	std::vector<std::string> LuauObjectScript::getProperties() {
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
