#include "ve/io/gfx/shader.hpp"
#include <filesystem>
#include <fstream>
#include <glbinding/gl/boolean.h>
#include <glbinding/gl/enum.h>
#include <glbinding/gl/functions.h>
#include <glbinding/gl/types.h>
#include <iostream>
#include <sstream>

namespace VoidEngine::IO::GFX {
	using namespace gl;

	FileShaderSourceProvider::FileShaderSourceProvider(std::filesystem::path& path) {
		std::ostringstream str;
		std::ifstream in(path);
		str << in.rdbuf();
		source = str.str();
	}

	std::string FileShaderSourceProvider::getSourceCode() {
		return source;
	}

	Shader::Shader(IShaderSourceProvider& vertex, IShaderSourceProvider& fragment) {
		std::string vtxSource = vertex.getSourceCode(), frgSource = fragment.getSourceCode();
		GLint vtxShader = glCreateShader(GL_VERTEX_SHADER), frgShader = glCreateShader(GL_FRAGMENT_SHADER);

		GLint success = 0;
		char const* vtxPtr = vtxSource.c_str();
		glShaderSource(vtxShader, 1, &vtxPtr, nullptr);
		glCompileShader(vtxShader);
		glGetShaderiv(vtxShader, GL_COMPILE_STATUS, &success);
		if(!success) {
			GLint logLen;
			glGetShaderiv(vtxShader, GL_INFO_LOG_LENGTH, &logLen);
			char* log = new char[logLen];
			glGetShaderInfoLog(vtxShader, logLen, nullptr, log);
			std::cerr << log << std::endl;
			delete[] log;
		}

		char const* frgPtr = frgSource.c_str();
		glShaderSource(frgShader, 1, &frgPtr, nullptr);
		glCompileShader(frgShader);
		glGetShaderiv(frgShader, GL_COMPILE_STATUS, &success);
		if(!success) {file:///home/shadowflare/Pictures/Reddit/RDT_20250105_2136265067489471474656270.gif
			GLint logLen;
			glGetShaderiv(frgShader, GL_INFO_LOG_LENGTH, &logLen);
			char* log = new char[logLen];
			glGetShaderInfoLog(frgShader, logLen, nullptr, log);
			std::cerr << log << std::endl;
			delete[] log;
		}

		program = glCreateProgram();
		glAttachShader(program, vtxShader);
		glAttachShader(program, frgShader);
		glLinkProgram(program);

		glGetProgramiv(program, GL_LINK_STATUS, &success);
		if(!success) {
			GLint logLen;
			glGetProgramiv(program, GL_INFO_LOG_LENGTH, &logLen);
			char* log = new char[logLen];
			glGetProgramInfoLog(program, logLen, nullptr, log);
			std::cerr << log << std::endl;
			delete[] log;
		}

		glDeleteShader(vtxShader);
		glDeleteShader(frgShader);
	}

	Shader::~Shader() {
		glDeleteProgram(program);
	}

	void Shader::bind() {
		glUseProgram(program);
	}
}

