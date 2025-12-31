#pragma once

#include <filesystem>
#include <glbinding/gl/types.h>
#include <string>
#include <glbinding/gl46core/gl.h>

namespace VoidEngine::IO::GFX {
	using namespace gl;
	class IShaderSourceProvider {
	public:
		[[nodiscard]] virtual std::string getSourceCode() = 0;
	};

	class FileShaderSourceProvider : public IShaderSourceProvider {
		std::string source;
	public:
		FileShaderSourceProvider(std::filesystem::path& path);
		[[nodiscard]] std::string getSourceCode();
	};

	class Shader {
		GLint program = 0;
	public:
		Shader(IShaderSourceProvider& vertex, IShaderSourceProvider& fragment);
		~Shader();

		void bind();
	};
}

