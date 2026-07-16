#include "ve/io/gfx/dummy/graphics_program_dummy.hpp"
#include <memory>
#include <optional>

namespace VoidEngine::IO::GFX::Dummy {
	DummyGraphicsProgram::DummyGraphicsProgram() {}

	std::shared_ptr<DummyGraphicsProgram> DummyGraphicsProgram::create() {
		return std::shared_ptr<DummyGraphicsProgram>(new DummyGraphicsProgram);
	}

	void DummyGraphicsProgram::draw(std::shared_ptr<Mesh>) {}

	constexpr std::vector<Uniform>& DummyGraphicsProgram::getUniforms() { return uniforms; }
	std::optional<Uniform> DummyGraphicsProgram::queryUniform(std::string name) { return std::nullopt; }
	void DummyGraphicsProgram::setUniform(Uniform&, std::vector<float>&) {}
	void DummyGraphicsProgram::setUniform(Uniform&, std::vector<int32_t>&) {}
	void DummyGraphicsProgram::setUniform(Uniform&, std::vector<glm::vec2>&) {}
	void DummyGraphicsProgram::setUniform(Uniform&, std::vector<glm::vec3>&) {}
	void DummyGraphicsProgram::setUniform(Uniform&, std::vector<glm::vec4>&) {}
	void DummyGraphicsProgram::setUniform(Uniform&, std::vector<glm::ivec2>&) {}
	void DummyGraphicsProgram::setUniform(Uniform&, std::vector<glm::ivec3>&) {}
	void DummyGraphicsProgram::setUniform(Uniform&, std::vector<glm::ivec4>&) {}
	void DummyGraphicsProgram::setUniform(Uniform&, std::vector<glm::mat4>&) {}
	void DummyGraphicsProgram::setUniform(Uniform&, std::vector<shared_ptr<Texture>>&) {}
	void DummyGraphicsProgram::setUniform(Uniform&, float const&) {}
	void DummyGraphicsProgram::setUniform(Uniform&, int32_t const&) {}
	void DummyGraphicsProgram::setUniform(Uniform&, glm::vec2 const&) {}
	void DummyGraphicsProgram::setUniform(Uniform&, glm::vec3 const&) {}
	void DummyGraphicsProgram::setUniform(Uniform&, glm::vec4 const&) {}
	void DummyGraphicsProgram::setUniform(Uniform&, glm::ivec2 const&) {}
	void DummyGraphicsProgram::setUniform(Uniform&, glm::ivec3 const&) {}
	void DummyGraphicsProgram::setUniform(Uniform&, glm::ivec4 const&) {}
	void DummyGraphicsProgram::setUniform(Uniform&, glm::mat4 const&) {}
	void DummyGraphicsProgram::setUniform(Uniform&, std::shared_ptr<Texture> const&) {}
}