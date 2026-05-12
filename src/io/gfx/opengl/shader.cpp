#include "ve/io/gfx/opengl/shader.hpp"
#include <cstdint>
#include <glbinding/gl/boolean.h>
#include <glbinding/gl/enum.h>
#include <glbinding/gl/functions.h>
#include <glbinding/gl46core/gl.h>
#include <format>
#include <stdexcept>

namespace VoidEngine::IO::GFX::OpenGL {
	using namespace gl;

	GLShader::GLShader(ShaderType type, VoidEngine::IO::ResourceProviders::AShaderSourceProvider& sourceCode) : Shader(type) {
		std::string sourceStr = sourceCode.getShaderSource();
		const char *sourceCStr = sourceStr.c_str();

		GLenum glShaderType = GL_INVALID_VALUE;
		switch(type) {
		case VERTEX:
			glShaderType = GL_VERTEX_SHADER;
			break;
		case FRAGMENT:
			glShaderType = GL_FRAGMENT_SHADER;
			break;
		}

		if(glShaderType == GL_INVALID_VALUE) throw std::runtime_error(std::format("ShaderType ({}) was invalid!", (uint8_t) type));

		shader = glCreateShader(glShaderType);
		glShaderSource(shader, 1, &sourceCStr, nullptr);
		glCompileShader(shader);

		int32_t success = 0;
		glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
		if(!success) {
			int32_t len = 0;
			glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &len);

			char *log = new char[len];
			glGetShaderInfoLog(shader, len, nullptr, log);
			auto err = std::runtime_error(log);
			delete[] log;
			throw err;
		}
	}

	GLShader::~GLShader() {
		glDeleteShader(shader);
	}
}

