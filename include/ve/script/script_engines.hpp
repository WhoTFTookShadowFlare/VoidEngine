#pragma once

#include <map>
#include <memory>
#include "ve/io/res_providers/source/a_provider.hpp"
#include "ve/script/a_script_engine.hpp"
#include "ve/script/a_script_module.hpp"

namespace VoidEngine::Scripts {
	class ScriptEngines final {
	private:
		std::map<std::string, std::shared_ptr<AScriptEngine>> engines;

		static std::shared_ptr<ScriptEngines> instance;
		ScriptEngines();
	public:
		static std::shared_ptr<ScriptEngines> getInstance();
		~ScriptEngines();

		std::shared_ptr<Script> compileScript(std::shared_ptr<IO::ResourceProviders::ASourceProvider>);
		std::shared_ptr<AScriptModule> compileModuleScript(std::shared_ptr<IO::ResourceProviders::ASourceProvider>);
	};
}
