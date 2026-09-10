#pragma once

#include "ve/script/a_script_engine.hpp"
#include <memory>

namespace VoidEngine::Scripts {
	class Script {
	private:
		std::shared_ptr<IO::ResourceProviders::ASourceProvider> code;
	protected:
		Script(std::shared_ptr<IO::ResourceProviders::ASourceProvider>);
		std::shared_ptr<IO::ResourceProviders::ASourceProvider> getCode();
	public:
		virtual ~Script();
		virtual void execute() = 0;
		virtual std::shared_ptr<AScriptEngine> getScriptEngine() = 0;
	};
}
