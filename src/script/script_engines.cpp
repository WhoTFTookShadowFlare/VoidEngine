#include "ve/script/script_engines.hpp"
#include "ve/io/res_providers/source/a_provider.hpp"
#include "ve/script/a_script_engine.hpp"
#include "ve/script/script.hpp"
#include <memory>

namespace VoidEngine::Scripts {
	std::shared_ptr<ScriptEngines> ScriptEngines::instance = nullptr;

	ScriptEngines::ScriptEngines() {
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
