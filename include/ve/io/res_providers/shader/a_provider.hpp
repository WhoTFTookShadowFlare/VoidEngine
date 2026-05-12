#pragma once

#include <string>

namespace VoidEngine::IO::ResourceProviders {
	class AShaderSourceProvider {
	public:
		virtual std::string getShaderSource() = 0;
	};
}
