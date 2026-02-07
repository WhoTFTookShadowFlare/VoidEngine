#pragma once

#include "ve/io/gfx/graphics_program.hpp"
#include "ve/io/gfx/shader.hpp"
#include <cstdint>
#include <vector>
#include <memory>

namespace VoidEngine::IO::GFX::OpenGL {
	using std::shared_ptr;
	class GLGraphicsProgram : public GraphicsProgram {
		uint32_t program = 0;
		std::vector<Uniform> uniforms;
	public:
		GLGraphicsProgram(shared_ptr<Shader>, shared_ptr<Shader>);
		~GLGraphicsProgram();

		void draw(shared_ptr<Mesh>);

		std::vector<Uniform> getUniforms();

		void setUniform(Uniform&, vector<float>&);
		void setUniform(Uniform&, vector<int32_t>&);

		void setUniform(Uniform&, vector<glm::vec2>&);
		void setUniform(Uniform&, vector<glm::vec3>&);
		void setUniform(Uniform&, vector<glm::vec4>&);
		void setUniform(Uniform&, vector<glm::ivec2>&);
		void setUniform(Uniform&, vector<glm::ivec3>&);
		void setUniform(Uniform&, vector<glm::ivec4>&);
		void setUniform(Uniform&, vector<glm::mat4>&);

		void setUniform(Uniform&, vector<shared_ptr<Texture>>&);
	};
}

