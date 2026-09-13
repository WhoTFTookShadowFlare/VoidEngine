#include "api/lua_function.hpp"
#include "api/lua_object_script.hpp"
#include "lauxlib.h"
#include "lua.h"
#include "lua_script_engine.hpp"
#include "ve/class_db.hpp"
#include <memory>
#include <print>

namespace VoidEngine::Scripts::Lua::API {
	LuaFunction::~LuaFunction() {
		lua_State* state = LuaScriptEngine::getInstance()->state;
		lua_pushlightuserdata(state, this);
		lua_pushnil(state);
		lua_settable(state, LUA_REGISTRYINDEX);
	}

	LuaFunction::LuaFunction(std::string name, int funcIdx) : MethodBase(name) {
		lua_State* state = LuaScriptEngine::getInstance()->state;
		lua_pushlightuserdata(state, this);
		lua_pushvalue(state, funcIdx);
		lua_settable(state, LUA_REGISTRYINDEX);
	}

	Variant LuaFunction::call(std::shared_ptr<Object> obj, std::vector<Variant> args) const {
		if(obj->getScript() == nullptr) {
			std::println("[ERR] [Lua] Cannot call LuaFunction on object with no script");
			return nullptr;
		}
		
		if(obj->getScript()->getScriptEngine()->getLanguage() != "lua") {
			std::println("[ERR] [Lua] Cannot call LuaFunction on object whose script is not of language 'lua'");
			return nullptr;
		}

		auto luaEngine = LuaScriptEngine::getInstance();
		lua_State* state = luaEngine->state;
		std::shared_ptr<LuaObjectScript> script = std::static_pointer_cast<LuaObjectScript>(obj->getScript());

		lua_pushlightuserdata(state, const_cast<LuaFunction*>(this));
		lua_gettable(state, LUA_REGISTRYINDEX);
		script->pushObject(state);

		for(const auto& arg : args) {
			luaEngine->objectFromVariant(arg);
		}

		if(lua_pcall(state, args.size() + 1, 1, 0) != 0) {
			std::string err = luaL_checkstring(state, -1);
			std::println("[ERR] [Lua] {}", err);
			return nullptr;
		}

		int retVal = -1;
		return luaEngine->objectToVariant(&retVal);
	}

	int lua_FunctionNew(lua_State* state) {
		const std::string name = luaL_checkstring(state, 1);
		luaL_checktype(state, 2, LUA_TFUNCTION);

		LuaFunctionWrapper* function = static_cast<LuaFunctionWrapper*>(lua_newuserdata(state, sizeof(LuaFunctionWrapper)));
		luaL_getmetatable(state, "Function");
		lua_setmetatable(state, -2);

		function->method = new LuaFunction(name, 2);

		return 1;
	}

	int lua_Function__tostring(lua_State* state) {
		lua_pushstring(state, "NYI");
		return 1;
	}
	
	int lua_Function__eq(lua_State* state) {
		lua_pushboolean(state, false);
		return 1;
	}

	int luaopen_Function(lua_State* state) {
		luaL_newmetatable(state, "Function");
		luaL_setfuncs(state, functionLib, 0);
		lua_setglobal(state, "Function");
		return 0;
	}
}
