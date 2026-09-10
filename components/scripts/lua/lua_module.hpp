#pragma once

#include <ve/script/a_script_module.hpp>

extern "C" {
#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>
}

namespace VoidEngine::Scripts::Lua {
	class LuaModule final : public AScriptModule {
		friend class LuaScriptEngine;
	private:
		LuaModule(std::shared_ptr<IO::ResourceProviders::ASourceProvider>);

		bool pushModuleTable(lua_State*);
	public:
		std::shared_ptr<AScriptEngine> getScriptEngine();

		std::vector<std::string> getFunctions();
		Variant call(std::string fnName, std::vector<Variant> args);
		std::shared_ptr<AObjectScript> instanceObject();
	};
}