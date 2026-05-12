#pragma once

#include "ve/io/res_providers/shader/a_provider.hpp"

namespace VoidEngine::IO::ResourceProviders {
	class BasicShaderSourceProvider : public AShaderSourceProvider {
		std::string shaderSourceCode = "";
	public:
		BasicShaderSourceProvider(std::string shaderSourceCode) : shaderSourceCode(shaderSourceCode) {}

		std::string getShaderSource() { return shaderSourceCode; }
	};
}