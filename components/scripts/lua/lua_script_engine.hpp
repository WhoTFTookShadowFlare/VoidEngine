#pragma once

#include "api/lua_object_script.hpp"
#include <ve/script/a_script_engine.hpp>

extern "C" {
#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>
}

namespace VoidEngine::Scripts::Lua {
	namespace API {
		class LuaConstructor;
		class LuaObjectScript;
	}

	class LuaScriptEngine final : public AScriptEngine {
		friend class LuaScript;
		friend class LuaModule;

		friend class API::LuaConstructor;
		friend class API::LuaObjectScript;
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
