#include <lua_script_engine.hpp>

#include <print>
#include <lua_script.hpp>

namespace VoidEngine::Scripts::Lua {
	std::shared_ptr<LuaScriptEngine> LuaScriptEngine::instance = nullptr;

	LuaScriptEngine::LuaScriptEngine() {
		assert(instance == nullptr);

		std::println("[WARN] The lua script engine is still in development, expect issues");
		state = luaL_newstate();

		setupNativeTypes();

		luaL_openlibs(state);
		//luaL_sandbox(state); // TODO: sandbox lua
	}

	LuaScriptEngine::~LuaScriptEngine() {
		lua_close(state);
	}

	std::shared_ptr<LuaScriptEngine> LuaScriptEngine::getInstance() {
		if(instance == nullptr) instance = std::shared_ptr<LuaScriptEngine>(new LuaScriptEngine);
		return instance;
	}

	void LuaScriptEngine::setupNativeTypes() {}

	std::string LuaScriptEngine::getLanguage() { return "lua"; }

	std::shared_ptr<Script> LuaScriptEngine::compileScript(std::shared_ptr<IO::ResourceProviders::ASourceProvider> src) {
		return std::shared_ptr<LuaScript>(new LuaScript(src));
	}

	std::shared_ptr<AScriptModule> LuaScriptEngine::compileModuleScript(std::shared_ptr<IO::ResourceProviders::ASourceProvider>) {
		std::println("[WARN] compiling modules is NYI");
		return nullptr;
	}

	Variant LuaScriptEngine::objectToVariant(void*) {
		std::println("[WARN] Cannot convert lua object to a Variant, NYI");
		return nullptr;
	}

	void* LuaScriptEngine::objectFromVariant(Variant) {
		std::println("[WARN] Cannot convert Variant to a lua object, NYI");
		return nullptr;
	}
}
