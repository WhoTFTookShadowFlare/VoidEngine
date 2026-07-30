#pragma once

#include "ve/io/res_providers/source/a_provider.hpp"
#include "ve/variant.hpp"
#include <memory>

namespace VoidEngine::Scripts {
	class ScriptEngines;

	struct ByteCode {
		void* code;
		size_t size;
	};

	class Script;
	class AScriptModule;

	class AScriptEngine {
		friend class ScriptEngines;
	private:
	protected:
		virtual void setupNativeTypes() = 0;
	public:
		virtual std::shared_ptr<Script> compileScript(std::shared_ptr<IO::ResourceProviders::ASourceProvider>) = 0;
		virtual std::shared_ptr<AScriptModule> compileModuleScript(std::shared_ptr<IO::ResourceProviders::ASourceProvider>) = 0;

		virtual Variant objectToVariant(void*) = 0;
		virtual void* objectFromVariant(Variant) = 0;
	};
}
