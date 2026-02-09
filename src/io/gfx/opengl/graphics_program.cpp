#include "ve/io/gfx/opengl/graphics_program.hpp"
#include "ve/io/gfx/mesh.hpp"
#include "ve/io/gfx/opengl/shader.hpp"
#include "ve/io/gfx/program_uniform.hpp"
#include "ve/io/gfx/shader.hpp"
#include <cstdint>
#include <glbinding/gl/enum.h>
#include <glbinding/gl/functions.h>
#include <glbinding/gl46core/gl.h>
#include <stdexcept>
#include <string>
#include <vector>

namespace VoidEngine::IO::GFX::OpenGL {
	using namespace gl;

	GLGraphicsProgram::GLGraphicsProgram(shared_ptr<Shader> vtx, shared_ptr<Shader> frg) {
		GLShader *vertex = static_cast<GLShader*>(vtx.get());
		GLShader *fragment = static_cast<GLShader*>(frg.get());
		
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

		int32_t count = 0, maxNameLength = 0;
		glGetProgramiv(program, GL_ACTIVE_UNIFORMS, &count);
		glGetProgramiv(program, GL_ACTIVE_UNIFORM_MAX_LENGTH, &maxNameLength);

		for(int32_t idx = 0; idx < count; idx++) {
			char *name = new char[maxNameLength];
			GLenum glType = GL_INVALID_VALUE;
			glGetActiveUniform(program, idx, maxNameLength, nullptr, nullptr, &glType, name);
			int32_t location = glGetUniformLocation(program, name);

			UniformType type = UniformType::INVALID;
			switch(glType) {
				case GL_FLOAT: type = UniformType::FLOAT; break;
				case GL_INT: type = UniformType::INT; break;

				case GL_FLOAT_VEC2: type = UniformType::VECTOR_2F; break;
				case GL_FLOAT_VEC3: type = UniformType::VECTOR_3F; break;
				case GL_FLOAT_VEC4: type = UniformType::VECTOR_4F; break;
				case GL_INT_VEC2: type = UniformType::VECTOR_2I; break;
				case GL_INT_VEC3: type = UniformType::VECTOR_3I; break;
				case GL_INT_VEC4: type = UniformType::VECTOR_4I; break;
				
				case GL_FLOAT_MAT4: type = UniformType::MATRIX_4X4F; break;

				case GL_SAMPLER_2D: type = UniformType::SAMPLER_2D; break;
				default: break;
			};

			uniforms.push_back(createUniform(name, location, type));
			delete[] name;
		}
	}

	GLGraphicsProgram::~GLGraphicsProgram() {
		glDeleteProgram(program);
	}

	void GLGraphicsProgram::draw(shared_ptr<Mesh> mesh) {
		glUseProgram(program);
		forwardDraw(mesh);
		glUseProgram(0);
	}

	constexpr std::vector<Uniform>& GLGraphicsProgram::getUniforms() {
		return uniforms;
	}

	void GLGraphicsProgram::setUniform(Uniform& uniform, std::vector<float>& data) {
		glUseProgram(program);
		glUniform1fv(uniform.getLocation(), data.size(), data.data());
		glUseProgram(0);
	}

	void GLGraphicsProgram::setUniform(Uniform& uniform, vector<int32_t>& data) {
		glUseProgram(program);
		glUniform1iv(uniform.getLocation(), data.size(), data.data());
		glUseProgram(0);
	}

	void GLGraphicsProgram::setUniform(Uniform& uniform, vector<glm::vec2>& data) {
		glUseProgram(program);
		glUniform2fv(uniform.getLocation(), data.size(), (float*) data.data());
		glUseProgram(0);
	}

	void GLGraphicsProgram::setUniform(Uniform& uniform, vector<glm::vec3>& data) {
		glUseProgram(program);
		glUniform3fv(uniform.getLocation(), data.size(), (float*) data.data());
		glUseProgram(0);
	}

	void GLGraphicsProgram::setUniform(Uniform& uniform, vector<glm::vec4>& data) {
		glUseProgram(program);
		glUniform4fv(uniform.getLocation(), data.size(), (float*) data.data());
		glUseProgram(0);
	}

	void GLGraphicsProgram::setUniform(Uniform& uniform, vector<glm::ivec2>& data) {
		glUseProgram(program);
		glUniform2iv(uniform.getLocation(), data.size(), (int32_t*) data.data());
		glUseProgram(0);

	}

	void GLGraphicsProgram::setUniform(Uniform& uniform, vector<glm::ivec3>& data) {
		glUseProgram(program);
		glUniform3iv(uniform.getLocation(), data.size(), (int32_t*) data.data());
		glUseProgram(0);
	}

	void GLGraphicsProgram::setUniform(Uniform& uniform, vector<glm::ivec4>& data) {
		glUseProgram(program);
		glUniform4iv(uniform.getLocation(), data.size(), (int32_t*) data.data());
		glUseProgram(0);
	}

	void GLGraphicsProgram::setUniform(Uniform& uniform, std::vector<glm::mat4>& data) {
		glUseProgram(program);
		glUniformMatrix4fv(uniform.getLocation(), data.size(), false, reinterpret_cast<float*>(data.data()));
		glUseProgram(0);
	}

	void GLGraphicsProgram::setUniform(Uniform& uniform, vector<shared_ptr<Texture>>& data) {
		std::vector<int32_t> texSlots(data.size());
		for(size_t idx = 0; idx < data.size(); idx++) {
			if(data[idx]) texSlots[idx] = data[idx]->getTextureSlot();
			else data[idx] = 0;
		}
		setUniform(uniform, texSlots);
	}
}

