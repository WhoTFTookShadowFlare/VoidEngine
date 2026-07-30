#include "ve/script/script_engines.hpp"
#include "ve/io/res_providers/source/a_provider.hpp"
#include "ve/script/a_script_engine.hpp"
#include "ve/script/script.hpp"
#include <memory>

#ifdef COMPONENT_SCRIPTS_LUAU_ENABLED
#include "luau_script_engine.hpp"
#endif

namespace VoidEngine::Scripts {
	std::shared_ptr<ScriptEngines> ScriptEngines::instance = nullptr;

	ScriptEngines::ScriptEngines() {
#ifdef COMPONENT_SCRIPTS_LUAU_ENABLED
		{
			std::shared_ptr<AScriptEngine> luauEngine = Luau::LuauScriptEngine::getInstance();
			engines["luau"] = luauEngine;
			luauEngine->setupNativeTypes();
		}
#endif // COMPONENT_SCRIPTS_LUAU_ENABLED
	}

	ScriptEngines::~ScriptEngines() {

	}

	std::shared_ptr<ScriptEngines> ScriptEngines::getInstance() {
		if(instance == nullptr) instance = std::shared_ptr<ScriptEngines>(new ScriptEngines);
		return instance;
	}

	std::shared_ptr<Script> ScriptEngines::compileScript(std::shared_ptr<IO::ResourceProviders::ASourceProvider> srcProvider) {
		if(!engines.contains(srcProvider->getLanguage())) return nullptr;
		return engines[srcProvider->getLanguage()]->compileScript(srcProvider);
	}

	std::shared_ptr<AScriptModule> ScriptEngines::compileModuleScript(std::shared_ptr<IO::ResourceProviders::ASourceProvider> srcProvider) {
		if(!engines.contains(srcProvider->getLanguage())) return nullptr;
		return engines[srcProvider->getLanguage()]->compileModuleScript(srcProvider);
	}
}
