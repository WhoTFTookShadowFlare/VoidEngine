#pragma once

#include <string>

namespace VoidEngine::IO::ResourceProviders {
	class ASourceProvider {
	public:
		virtual std::string getShaderSource() = 0;
		virtual std::string getLanguage() = 0;
	};
}
