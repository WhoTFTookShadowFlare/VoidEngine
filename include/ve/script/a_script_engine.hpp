#pragma once

#include "ve/io/res_providers/source/a_provider.hpp"
#include "ve/variant.hpp"
#include <memory>

namespace VoidEngine::Scripts {
	struct ByteCode {
		void* code;
		size_t size;
	};

	class Script;

	class AScriptEngine {
	private:
	public:
		virtual std::shared_ptr<Script> compileScript(std::shared_ptr<IO::ResourceProviders::ASourceProvider>) = 0;

		virtual Variant objectToVariant(void*) = 0;
		virtual void* objectFromVariant(Variant) = 0;
	};
}
