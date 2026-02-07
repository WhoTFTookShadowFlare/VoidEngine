#pragma once

#include "ve/io/gfx/mesh.hpp"
#include "ve/io/gfx/program_uniform.hpp"
#include "ve/io/gfx/renderer_backend.hpp"
#include <cstdint>
#include <glm/ext/vector_float2.hpp>
#include <vector>
#include <string>
#include <memory>
#include <glm/ext/matrix_float4x4.hpp>

namespace VoidEngine::IO::GFX {
	using std::vector;

	class Texture;

	class GraphicsProgram {
	protected:
		void forwardDraw(std::shared_ptr<Mesh> mesh) { mesh->draw(); }
		Uniform createUniform(std::string name, int32_t location, UniformType type) { return Uniform { name, location, type }; }
	public:
		virtual ~GraphicsProgram() {}

		virtual void draw(std::shared_ptr<Mesh>) = 0;

		virtual std::vector<Uniform> getUniforms() = 0;

		virtual void setUniform(Uniform&, vector<float>&) = 0;
		virtual void setUniform(Uniform&, vector<int32_t>&) = 0;

		virtual void setUniform(Uniform&, vector<glm::vec2>&) = 0;
		virtual void setUniform(Uniform&, vector<glm::vec3>&) = 0;
		virtual void setUniform(Uniform&, vector<glm::vec4>&) = 0;
		virtual void setUniform(Uniform&, vector<glm::ivec2>&) = 0;
		virtual void setUniform(Uniform&, vector<glm::ivec3>&) = 0;
		virtual void setUniform(Uniform&, vector<glm::ivec4>&) = 0;
		virtual void setUniform(Uniform&, vector<glm::mat4>&) = 0;

		virtual void setUniform(Uniform&, vector<shared_ptr<Texture>>&) = 0;
	};
}

