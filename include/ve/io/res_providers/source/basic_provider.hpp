#pragma once

#include "a_provider.hpp"
#include "ve/io/res_providers/source/a_provider.hpp"

namespace VoidEngine::IO::ResourceProviders {
	class BasicSourceProvider : public ASourceProvider {
		std::string shaderSourceCode = "";
	public:
		BasicSourceProvider(std::string shaderSourceCode) : shaderSourceCode(shaderSourceCode) {}

		std::string getShaderSource() { return shaderSourceCode; }
	};
}