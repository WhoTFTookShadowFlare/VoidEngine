#pragma once

namespace VoidEngine::IO::GFX {
	enum ShaderType {
		VERTEX,
		FRAGMENT,
	};

	class Shader {
		ShaderType type;
	public:
		Shader(ShaderType type) : type(type) {}
		virtual ~Shader() {}
	};
}

