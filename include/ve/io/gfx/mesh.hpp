#pragma once

#include <cstdint>
#include <glm/ext/vector_float3.hpp>
#include <glbinding/gl/types.h>
#include <glbinding/gl46core/gl.h>
#include <vector>

namespace VoidEngine::IO::GFX {
	using namespace gl;
	struct Vertex {
		glm::vec3 position;
	};

	class Mesh {
		GLuint VAO, VBO, EBO;
		std::vector<Vertex> vertices;
		std::vector<uint32_t> indices;

	public:
		Mesh();
		~Mesh();

		void bind();

		void setVertexData(std::vector<Vertex> vertices);
		void setIndexData(std::vector<uint32_t> indices);

		void draw();
	};
}

