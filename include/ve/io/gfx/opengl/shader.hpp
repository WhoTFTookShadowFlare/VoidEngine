#pragma once

#include "ve/io/gfx/shader.hpp"
#include "ve/io/gfx/shader_source_provider.hpp"
#include <cstdint>

namespace VoidEngine::IO::GFX::OpenGL {
	class GLGraphicsProgram;
	class GLShader : public Shader {
		friend class GLGraphicsProgram;
		uint32_t shader = 0;
	public:
		GLShader(ShaderType type, AShaderSourceProvider& sourceCode);
		~GLShader();
	};
}

