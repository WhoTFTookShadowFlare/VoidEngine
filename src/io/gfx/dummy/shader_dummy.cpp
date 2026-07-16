#include "ve/io/gfx/dummy/shader_dummy.hpp"
#include "ve/io/gfx/shader.hpp"
#include <memory>

namespace VoidEngine::IO::GFX::Dummy {
	DummyShader::DummyShader(ShaderType type) : Shader(type) {}

	std::shared_ptr<DummyShader> DummyShader::create(ShaderType type) {
		return std::shared_ptr<DummyShader>(new DummyShader(type));
	}
}
