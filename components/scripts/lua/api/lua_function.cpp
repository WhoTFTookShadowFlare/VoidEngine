#include "api/lua_function.hpp"
#include "api/lua_object_script.hpp"
#include "api/lua_object.hpp"
#include "lauxlib.h"
#include "lua.h"
#include "lua_script_engine.hpp"
#include "ve/class_db.hpp"
#include <memory>
#include <print>

namespace VoidEngine::Scripts::Lua::API {
	LuaFunction::LuaFunction(std::string name, int funcIdx) : MethodBase(name) {
		lua_State* state = LuaScriptEngine::getInstance()->state;
		lua_pushlightuserdata(state, this);
		lua_pushvalue(state, (funcIdx < 0) ? funcIdx - 1 : funcIdx);
		lua_settable(state, LUA_REGISTRYINDEX);
	}
	
	LuaFunction::~LuaFunction() {
		lua_State* state = LuaScriptEngine::getInstance()->state;
		lua_pushlightuserdata(state, this);
		lua_pushnil(state);
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

	LuaFunctionWrapper* lua_pushfunctionwrapper(lua_State* state) {
		LuaFunctionWrapper* function = static_cast<LuaFunctionWrapper*>(lua_newuserdata(state, sizeof(LuaFunctionWrapper)));
		luaL_getmetatable(state, "Function");
		lua_setmetatable(state, -2);
		return function;
	}

	int lua_FunctionNew(lua_State* state) {
		const std::string name = luaL_checkstring(state, 1);
		luaL_checktype(state, 2, LUA_TFUNCTION);

		LuaFunctionWrapper* function = lua_pushfunctionwrapper(state);
		function->method = new LuaFunction(name, 2);

		return 1;
	}

	int lua_Function__index(lua_State* state) {
		LuaFunctionWrapper* func = static_cast<LuaFunctionWrapper*>(luaL_checkudata(state, 1, "Function"));

		std::string idxName = lua_tostring(state, 2);
		lua_getmetatable(state, 1);
		lua_getfield(state, -1, idxName.c_str());
		return 1;
	}

	int lua_Function__tostring(lua_State* state) {
		LuaFunctionWrapper* function = static_cast<LuaFunctionWrapper*>(luaL_checkudata(state, 1, "Function"));
		lua_pushstring(state, function->method->getName().c_str());
		return 1;
	}
	
	int lua_Function__eq(lua_State* state) {
		LuaFunctionWrapper* LHS = static_cast<LuaFunctionWrapper*>(luaL_checkudata(state, 1, "Function"));
		LuaFunctionWrapper* RHS = static_cast<LuaFunctionWrapper*>(luaL_checkudata(state, 1, "Function"));
		lua_pushboolean(state, LHS->method == RHS->method);
		return 1;
	}

	int lua_Function__call(lua_State* state) {
		LuaFunctionWrapper* function = static_cast<LuaFunctionWrapper*>(luaL_checkudata(state, 1, "Function"));
		LuaObjectWrapper* object = static_cast<LuaObjectWrapper*>(luaL_checkudata(state, 2, "Object"));

		std::println("Function __call NYI");

		return 0;
	}

	int luaopen_Function(lua_State* state) {
		luaL_newmetatable(state, "Function");
		luaL_setfuncs(state, functionLib, 0);
		lua_setglobal(state, "Function");
		return 0;
	}
}
