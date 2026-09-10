#pragma once

#include <ve/script/a_script_engine.hpp>

extern "C" {
#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>
}

namespace VoidEngine::Scripts::Lua {
	class LuaScriptEngine final : public AScriptEngine {
		friend class LuaScript;
	private:
		static std::shared_ptr<LuaScriptEngine> instance;

		lua_State* state = nullptr;
	protected:
		void setupNativeTypes();

	public:
		LuaScriptEngine();
		~LuaScriptEngine();

		static std::shared_ptr<LuaScriptEngine> getInstance();

		std::string getLanguage();

		std::shared_ptr<Script> compileScript(std::shared_ptr<IO::ResourceProviders::ASourceProvider>);
		std::shared_ptr<AScriptModule> compileModuleScript(std::shared_ptr<IO::ResourceProviders::ASourceProvider>);

		Variant objectToVariant(void*);
		void* objectFromVariant(Variant);
	};
}
