#include "graphics_program_opengl.hpp"
#include "ve/io/gfx/mesh.hpp"
#include "shader_opengl.hpp"
#include "ve/io/gfx/program_uniform.hpp"
#include "ve/io/gfx/renderer.hpp"
#include "ve/io/gfx/shader.hpp"
#include <algorithm>
#include <cstdint>
#include <glbinding/gl/enum.h>
#include <glbinding/gl/functions.h>
#include <glbinding/gl46core/gl.h>
#include <optional>
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
			GLint uniformSize = 0; // Prevents crash on windows
			glGetActiveUniform(program, idx, maxNameLength, nullptr, &uniformSize, &glType, name);
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

			auto uniform = createUniform(name, location, type);
			uniforms.push_back(uniform);
			delete[] name;
		}
	}

	GLGraphicsProgram::~GLGraphicsProgram() {
		glDeleteProgram(program);
	}

	void GLGraphicsProgram::draw(shared_ptr<Mesh> mesh) {
		auto material = mesh->getMaterial();
		if(material == nullptr) {
			glUseProgram(program);
			forwardDraw(mesh);
			glUseProgram(0);
			return;
		}

		auto optUniformAlbedoTexture = queryUniform("material.albedo");
		if(optUniformAlbedoTexture.has_value()) {
			setUniform(optUniformAlbedoTexture.value(), material->getAlbedoTexture());
			material->getAlbedoTexture()->bindTexture();
		}

		auto optUniformCameraPosition = queryUniform("cameraPosition");
		if(optUniformCameraPosition.has_value()) {
			setUniform(optUniformCameraPosition.value(), Renderer::getInstance()->getCameraPosition());
		}

		glUseProgram(program);
		forwardDraw(mesh);
		glUseProgram(0);
	}

	constexpr std::vector<Uniform>& GLGraphicsProgram::getUniforms() {
		return uniforms;
	}

	std::optional<Uniform> GLGraphicsProgram::queryUniform(std::string name) {
		auto idx = std::find_if(uniforms.cbegin(), uniforms.cend(), [&name](const auto& uniform) {
			return uniform.getName() == name;
		});
		if(idx == uniforms.cend()) return std::nullopt;
		return *idx;
	}

	void GLGraphicsProgram::setUniform(Uniform& uniform, std::vector<float>& data) {
		glUseProgram(program);
		glUniform1fv(uniform.getLocation(), data.size(), data.data());
		glUseProgram(0);
	}

	void GLGraphicsProgram::setUniform(Uniform& uniform, std::vector<int32_t>& data) {
		glUseProgram(program);
		glUniform1iv(uniform.getLocation(), data.size(), data.data());
		glUseProgram(0);
	}

	void GLGraphicsProgram::setUniform(Uniform& uniform, std::vector<glm::vec2>& data) {
		glUseProgram(program);
		glUniform2fv(uniform.getLocation(), data.size(), (float*) data.data());
		glUseProgram(0);
	}

	void GLGraphicsProgram::setUniform(Uniform& uniform, std::vector<glm::vec3>& data) {
		glUseProgram(program);
		glUniform3fv(uniform.getLocation(), data.size(), (float*) data.data());
		glUseProgram(0);
	}

	void GLGraphicsProgram::setUniform(Uniform& uniform, std::vector<glm::vec4>& data) {
		glUseProgram(program);
		glUniform4fv(uniform.getLocation(), data.size(), (float*) data.data());
		glUseProgram(0);
	}

	void GLGraphicsProgram::setUniform(Uniform& uniform, std::vector<glm::ivec2>& data) {
		glUseProgram(program);
		glUniform2iv(uniform.getLocation(), data.size(), (int32_t*) data.data());
		glUseProgram(0);

	}

	void GLGraphicsProgram::setUniform(Uniform& uniform, std::vector<glm::ivec3>& data) {
		glUseProgram(program);
		glUniform3iv(uniform.getLocation(), data.size(), (int32_t*) data.data());
		glUseProgram(0);
	}

	void GLGraphicsProgram::setUniform(Uniform& uniform, std::vector<glm::ivec4>& data) {
		glUseProgram(program);
		glUniform4iv(uniform.getLocation(), data.size(), (int32_t*) data.data());
		glUseProgram(0);
	}

	void GLGraphicsProgram::setUniform(Uniform& uniform, std::vector<glm::mat4>& data) {
		glUseProgram(program);
		glUniformMatrix4fv(uniform.getLocation(), data.size(), false, reinterpret_cast<float*>(data.data()));
		glUseProgram(0);
	}

	void GLGraphicsProgram::setUniform(Uniform& uniform, std::vector<shared_ptr<Texture>>& data) {
		std::vector<int32_t> texSlots(data.size());
		for(size_t idx = 0; idx < data.size(); idx++) {
			if(data[idx]) texSlots[idx] = data[idx]->getTextureSlot();
			else data[idx] = 0;
		}
		setUniform(uniform, texSlots);
	}

	void GLGraphicsProgram::setUniform(Uniform& uniform, float const& value) {
		glUseProgram(program);
		glUniform1f(uniform.getLocation(), value);
		glUseProgram(0);
	}

	void GLGraphicsProgram::setUniform(Uniform& uniform, int32_t const& value) {
		glUseProgram(program);
		glUniform1i(uniform.getLocation(), value);
		glUseProgram(0);
	}

	void GLGraphicsProgram::setUniform(Uniform& uniform, glm::vec2 const& value) {
		glUseProgram(program);
		glUniform2f(uniform.getLocation(), value.x, value.y);
		glUseProgram(0);
	}

	void GLGraphicsProgram::setUniform(Uniform& uniform, glm::vec3 const& value) {
		glUseProgram(program);
		glUniform3f(uniform.getLocation(), value.x, value.y, value.z);
		glUseProgram(0);
	}

	void GLGraphicsProgram::setUniform(Uniform& uniform, glm::vec4 const& value) {
		glUseProgram(program);
		glUniform4f(uniform.getLocation(), value.x, value.y, value.z, value.w);
		glUseProgram(0);
	}

	void GLGraphicsProgram::setUniform(Uniform& uniform, glm::ivec2 const& value) {
		glUseProgram(program);
		glUniform2i(uniform.getLocation(), value.x, value.y);
		glUseProgram(0);
	}

	void GLGraphicsProgram::setUniform(Uniform& uniform, glm::ivec3 const& value) {
		glUseProgram(program);
		glUniform3i(uniform.getLocation(), value.x, value.y, value.z);
		glUseProgram(0);
	}

	void GLGraphicsProgram::setUniform(Uniform& uniform, glm::ivec4 const& value) {
		glUseProgram(program);
		glUniform4i(uniform.getLocation(), value.x, value.y, value.z, value.w);
		glUseProgram(0);
	}

	void GLGraphicsProgram::setUniform(Uniform& uniform, glm::mat4 const& value) {
		glUseProgram(program);
		glUniformMatrix4fv(uniform.getLocation(), 1, false, reinterpret_cast<const float*>(&value));
		glUseProgram(0);
	}

	void GLGraphicsProgram::setUniform(Uniform& uniform, std::shared_ptr<Texture> const& value) {
		setUniform(uniform, value->getTextureSlot());
	}
}

