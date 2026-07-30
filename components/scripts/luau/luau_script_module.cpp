#include "luau_script_module.hpp"
#include "lua.h"
#include "lualib.h"
#include "luau_script_engine.hpp"
#include "luau_script_object.hpp"
#include "ve/script/a_script_engine.hpp"
#include "ve/script/a_script_module.hpp"
#include "ve/script/a_script_object.hpp"
#include "ve/variant.hpp"
#include <algorithm>
#include <cstdint>
#include <memory>
#include <print>
#include <string>
#include <vector>

namespace VoidEngine::Scripts::Luau {
	LuauScriptModule::LuauScriptModule(ByteCode code) : AScriptModule(code) {	}

	std::shared_ptr<LuauScriptModule> LuauScriptModule::create(ByteCode code) {
		return std::shared_ptr<LuauScriptModule>(new LuauScriptModule(code));
	}

	std::shared_ptr<AScriptEngine> LuauScriptModule::getScriptEngine() {
		return LuauScriptEngine::getInstance();
	}

	std::vector<std::string> LuauScriptModule::getFunctions() {
		auto vmState = LuauScriptEngine::getInstance()->vmState;
		if(luau_load(vmState, "<unknown>", (const char*) getByteCode().code, getByteCode().size, 0)) {
			return {};
		}
		
		lua_pcall(vmState, 0, 1, 0);
		if(!lua_istable(vmState, -1)) {
			lua_pop(vmState, 1);
			return {};
		}

		std::vector<std::string> funcs;

		lua_pushnil(vmState);
		while(lua_next(vmState, -2)) {
			if(lua_type(vmState, -2) != LUA_TSTRING) {
				lua_pop(vmState, 1);
				continue;
			}
			funcs.push_back(luaL_checkstring(vmState, -2));
			lua_pop(vmState, 1);
		}

		lua_pop(vmState, 1);
		return funcs;
	}

	Variant LuauScriptModule::call(std::string fnName, std::vector<Variant> args) {
		auto engine = getScriptEngine();
		auto vmState = LuauScriptEngine::getInstance()->vmState;
		if(luau_load(vmState, "<unknown>", (const char*) getByteCode().code, getByteCode().size, 0)) {
			return {};
		}
		lua_pcall(vmState, 0, 1, 0);
		
		if(!lua_istable(vmState, -1)) {
			lua_pop(vmState, 1);
			return nullptr;
		}

		lua_getfield(vmState, -1, fnName.c_str());
		if(!lua_isfunction(vmState, -1)) {
			lua_pop(vmState, 2);
			return nullptr;
		}

		std::for_each(args.cbegin(), args.cend(), [&engine](const Variant& arg) {
			engine->objectFromVariant(arg);
		});

		lua_pcall(vmState, args.size(), 1, 0);
		uint32_t *top = new uint32_t(lua_gettop(vmState));
		Variant retVal = engine->objectToVariant(top);
		delete top;

		lua_pop(vmState, 1);
		return top;
	}

	std::shared_ptr<AScriptObject> LuauScriptModule::instanceObject() {
		auto engine = getScriptEngine();
		auto vmState = LuauScriptEngine::getInstance()->vmState;
		if(luau_load(vmState, "<unknown>", (const char*) getByteCode().code, getByteCode().size, 0)) {
			return {};
		}
		lua_pcall(vmState, 0, 1, 0);

		lua_getfield(vmState, -1, "create");
		if(!lua_isfunction(vmState, -1)) {
			std::println("Could not create object: missing function \"create()\"");
			lua_pop(vmState, 2);
			return nullptr;
		}

		lua_pcall(vmState, 0, 1, 0);
		std::shared_ptr<AScriptObject> instance = std::shared_ptr<AScriptObject>(new LuauScriptObject());

		lua_pop(vmState, 2);
		return instance;
	}
}