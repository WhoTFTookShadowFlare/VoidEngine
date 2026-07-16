#pragma once

#include "ve/io/gfx/shader.hpp"
#include <memory>

namespace VoidEngine::IO::GFX::Dummy {
	class DummyShader final : public Shader {
	private:
		DummyShader(ShaderType);
	public:
		static std::shared_ptr<DummyShader> create(ShaderType);
	};
}
