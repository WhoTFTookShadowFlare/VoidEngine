#include <lua_script.hpp>
#include <lua_script_engine.hpp>

#include <print>

namespace VoidEngine::Scripts::Lua {
	LuaScript::LuaScript(std::shared_ptr<IO::ResourceProviders::ASourceProvider> src) :
		Script(src)
	{	}

	LuaScript::~LuaScript() {	}

	void LuaScript::execute() {
		lua_State* state = LuaScriptEngine::getInstance()->state;

		int loadResult = luaL_loadstring(state, getCode()->getShaderSource().c_str());
		if(loadResult != 0) {
			std::println(
				"[ERR] Got {} when compiling a script:\n\t{}",
				loadResult == LUA_ERRSYNTAX ? "syntax error" : "out of memory",
				lua_tostring(state, -1)
			);
			lua_pop(state, 1);
			return;
		}

		int callResult = lua_pcall(state, 0, 0, 0);
		if(callResult != 0) {
			std::string errorHint = "";
			switch(callResult) {
				case LUA_ERRRUN: errorHint = "Runtime Error"; break;
				case LUA_ERRMEM: errorHint = "Out of Memory"; break;
				case LUA_ERRERR: errorHint = "Handler Call Fail"; break;
			}
			std::println(
				"[ERR] [Lua] ({}) {}",
				errorHint, lua_tostring(state, -1)
			);
			lua_pop(state, 1);
		}
	}

	std::shared_ptr<AScriptEngine> LuaScript::getScriptEngine() {
		return LuaScriptEngine::getInstance();
	}
}
