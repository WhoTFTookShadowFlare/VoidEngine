#include <lua_module.hpp>

#include <lua_script_engine.hpp>

namespace VoidEngine::Scripts::Lua {
	LuaModule::LuaModule(std::shared_ptr<IO::ResourceProviders::ASourceProvider> src) :
		AScriptModule(src)
	{	}

	bool LuaModule::pushModuleTable(lua_State* state) {
		int loadResult = luaL_loadstring(state, getCode()->getShaderSource().c_str());
		if (loadResult != 0) {
			std::println(
				"[ERR] Got {} when compiling a script:\n\t{}",
				loadResult == LUA_ERRSYNTAX ? "syntax error" : "out of memory",
				lua_tostring(state, -1)
			);
			lua_pop(state, 1);
			return true;
		}

		int callResult = lua_pcall(state, 0, 1, 0);
		if (callResult != 0) {
			std::string errorHint = "";
			switch (callResult) {
			case LUA_ERRRUN: errorHint = "Runtime Error"; break;
			case LUA_ERRMEM: errorHint = "Out of Memory"; break;
			case LUA_ERRERR: errorHint = "Handler Call Fail"; break;
			}
			std::println(
				"[ERR] [Lua] ({}) {}",
				errorHint, lua_tostring(state, -1)
			);
			lua_pop(state, 1);
			return true;
		}

		return false;
	}

	std::shared_ptr<AScriptEngine> LuaModule::getScriptEngine() {
		return LuaScriptEngine::getInstance();
	}

	std::vector<std::string> LuaModule::getFunctions() {
		std::println("Cannot get functions, NYI");
		return {};
	}

	Variant LuaModule::call(std::string fnName, std::vector<Variant> args) {
		auto engine = LuaScriptEngine::getInstance();
		lua_State* state = engine->state;

		if(pushModuleTable(state)) {
			std::println("[ERR] [Lua] Could not push module table");
			return nullptr;
		}

		lua_pushstring(state, fnName.c_str());
		lua_gettable(state, -2);

		if(lua_isnil(state, -1)) {
			std::println("[ERR] [Lua] Could not call function {}, got nil", fnName);
			lua_pop(state, 2);
			return nullptr;
		}

		if(!lua_isfunction(state, -1) && !lua_iscfunction(state, -1)) {
			std::println("[ERR] [Lua] Could call {}, not a function", fnName);
			lua_pop(state, 2);
			return nullptr;
		}

		for(Variant& arg : args) {
			engine->objectFromVariant(arg);
		}
		lua_pcall(state, args.size(), 1, 0);
		
		std::println("[WARN] [Lua] Cannot convert return value, NYI");
		lua_pop(state, 2);
		return nullptr;
	}

	std::shared_ptr<AObjectScript> LuaModule::instanceObject() {
		std::println("Cannot instance object, NYI");
		return nullptr;
	}
}
