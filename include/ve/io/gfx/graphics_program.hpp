#pragma once

#include "ve/io/gfx/mesh.hpp"
#include "ve/io/gfx/program_uniform.hpp"
#include "ve/io/gfx/renderer_backend.hpp"
#include <cstdint>
#include <glm/ext/vector_float2.hpp>
#include <optional>
#include <vector>
#include <string>
#include <memory>
#include <glm/ext/matrix_float4x4.hpp>

namespace VoidEngine::IO::GFX {
	class Texture;

	class GraphicsProgram {
	protected:
		void forwardDraw(std::shared_ptr<Mesh> mesh) { mesh->draw(); }
		Uniform createUniform(std::string name, int32_t location, UniformType type) { return Uniform { name, location, type }; }
	public:
		virtual ~GraphicsProgram() {}

		virtual void draw(std::shared_ptr<Mesh>) = 0;

		virtual constexpr std::vector<Uniform>& getUniforms() = 0;
		virtual std::optional<Uniform> queryUniform(std::string name) = 0;

		virtual void setUniform(Uniform&, std::vector<float>&) = 0;
		virtual void setUniform(Uniform&, std::vector<int32_t>&) = 0;

		virtual void setUniform(Uniform&, std::vector<glm::vec2>&) = 0;
		virtual void setUniform(Uniform&, std::vector<glm::vec3>&) = 0;
		virtual void setUniform(Uniform&, std::vector<glm::vec4>&) = 0;
		virtual void setUniform(Uniform&, std::vector<glm::ivec2>&) = 0;
		virtual void setUniform(Uniform&, std::vector<glm::ivec3>&) = 0;
		virtual void setUniform(Uniform&, std::vector<glm::ivec4>&) = 0;
		virtual void setUniform(Uniform&, std::vector<glm::mat4>&) = 0;

		virtual void setUniform(Uniform&, std::vector<shared_ptr<Texture>>&) = 0;

		virtual void setUniform(Uniform&, float const&) = 0;
		virtual void setUniform(Uniform&, int32_t const&) = 0;

		virtual void setUniform(Uniform&, glm::vec2 const&) = 0;
		virtual void setUniform(Uniform&, glm::vec3 const&) = 0;
		virtual void setUniform(Uniform&, glm::vec4 const&) = 0;
		virtual void setUniform(Uniform&, glm::ivec2 const&) = 0;
		virtual void setUniform(Uniform&, glm::ivec3 const&) = 0;
		virtual void setUniform(Uniform&, glm::ivec4 const&) = 0;
		virtual void setUniform(Uniform&, glm::mat4 const&) = 0;

		virtual void setUniform(Uniform&, std::shared_ptr<Texture> const&) = 0;
	};
}

