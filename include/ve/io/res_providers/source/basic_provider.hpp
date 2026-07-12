#pragma once

#include "a_provider.hpp"
#include "ve/io/res_providers/source/a_provider.hpp"

namespace VoidEngine::IO::ResourceProviders {
	class BasicSourceProvider : public ASourceProvider {
		std::string shaderSourceCode = "";
		std::string language = "";
	public:
		BasicSourceProvider(std::string shaderSourceCode, std::string language) : shaderSourceCode(shaderSourceCode), language(language) {}

		std::string getShaderSource() { return shaderSourceCode; }
		std::string getLanguage() { return language; }
	};
}