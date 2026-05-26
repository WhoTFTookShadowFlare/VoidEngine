#pragma once

#include <cstdint>

namespace VoidEngine::IO::GFX {
	enum ShaderType : uint8_t {
		VERTEX = 0,
		FRAGMENT,
	};

	class Shader {
		ShaderType type;
	public:
		Shader(ShaderType type) : type(type) {}
		virtual ~Shader() {}
	};
}
