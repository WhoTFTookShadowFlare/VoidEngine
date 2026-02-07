#pragma once

#include "ve/io/gfx/graphics_program.hpp"
#include "ve/io/gfx/shader.hpp"
#include <cstdint>
#include <vector>

namespace VoidEngine::IO::GFX::OpenGL {
	class GLGraphicsProgram : public GraphicsProgram {
		uint32_t program = 0, UBO = 0;
	public:
		GLGraphicsProgram(Shader*, Shader*);
		~GLGraphicsProgram();

		void draw(Mesh*);

		std::vector<Uniform> getUniforms();
	};
}

