#pragma once

#include "ve/io/gfx/graphics_program.hpp"
#include "ve/io/gfx/program_uniform.hpp"
#include <memory>
#include <vector>

namespace VoidEngine::IO::GFX::Dummy {
	class DummyGraphicsProgram final : public GraphicsProgram {
	private:
		std::vector<Uniform> uniforms = {
			createUniform("uProjection", 0, UniformType::MATRIX_4X4F),
			createUniform("uView", 0, UniformType::MATRIX_4X4F),
			createUniform("uModel", 0, UniformType::MATRIX_4X4F)
		};
		DummyGraphicsProgram();
	public:
		static std::shared_ptr<DummyGraphicsProgram> create();

		void draw(std::shared_ptr<Mesh>);

		constexpr std::vector<Uniform>& getUniforms();
		std::optional<Uniform> queryUniform(std::string name);

		void setUniform(Uniform&, std::vector<float>&);
		void setUniform(Uniform&, std::vector<int32_t>&);

		void setUniform(Uniform&, std::vector<glm::vec2>&);
		void setUniform(Uniform&, std::vector<glm::vec3>&);
		void setUniform(Uniform&, std::vector<glm::vec4>&);
		void setUniform(Uniform&, std::vector<glm::ivec2>&);
		void setUniform(Uniform&, std::vector<glm::ivec3>&);
		void setUniform(Uniform&, std::vector<glm::ivec4>&);
		void setUniform(Uniform&, std::vector<glm::mat4>&);

		void setUniform(Uniform&, std::vector<shared_ptr<Texture>>&);

		void setUniform(Uniform&, float const&);
		void setUniform(Uniform&, int32_t const&);

		void setUniform(Uniform&, glm::vec2 const&);
		void setUniform(Uniform&, glm::vec3 const&);
		void setUniform(Uniform&, glm::vec4 const&);
		void setUniform(Uniform&, glm::ivec2 const&);
		void setUniform(Uniform&, glm::ivec3 const&);
		void setUniform(Uniform&, glm::ivec4 const&);
		void setUniform(Uniform&, glm::mat4 const&);

		void setUniform(Uniform&, std::shared_ptr<Texture> const&);
	};
}
