#include "ve/io/gfx/opengl/graphics_program.hpp"
#include "ve/io/gfx/mesh.hpp"
#include "ve/io/gfx/opengl/shader.hpp"
#include <cstdint>
#include <glbinding/gl/enum.h>
#include <glbinding/gl/functions.h>
#include <glbinding/gl46core/gl.h>
#include <stdexcept>

namespace VoidEngine::IO::GFX::OpenGL {
	using namespace gl;

	GLGraphicsProgram::GLGraphicsProgram(Shader *vtx, Shader *frg) {
		GLShader *vertex = static_cast<GLShader*>(vtx);
		GLShader *fragment = static_cast<GLShader*>(frg);
		
		program = glCreateProgram();
		glAttachShader(program, vertex->shader);
		glAttachShader(program, fragment->shader);
		glLinkProgram(program);

		int32_t success = 0;
		glGetProgramiv(program, GL_LINK_STATUS, &success);
		if(!success) {
			int32_t len = 0;
			glGetProgramiv(program, GL_INFO_LOG_LENGTH, &len);
			char *log = new char[len];
			glGetProgramInfoLog(program, len, nullptr, log);
			auto err = std::runtime_error(log);
			delete[] log;
			throw err;
		}
	}

	GLGraphicsProgram::~GLGraphicsProgram() {
		glDeleteProgram(program);
	}

	void GLGraphicsProgram::draw(Mesh *mesh) {
		glUseProgram(program);
		forwardDraw(mesh);
		glUseProgram(0);
	}
}

