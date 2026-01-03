#include "ve/io/gfx/mesh.hpp"
#include <cstddef>
#include <cstdint>
#include <glbinding/gl/enum.h>
#include <glbinding/gl/functions.h>
#include <glm/ext/vector_float3.hpp>
#include <vector>

using namespace gl;

namespace VoidEngine::IO::GFX {
	Mesh::Mesh() {
		glGenVertexArrays(1, &VAO);
		glGenBuffers(1, &VBO);
		glGenBuffers(1, &EBO);
		setupVAO();
	}

	Mesh::~Mesh() {
		glDeleteVertexArrays(1, &VAO);
		glDeleteBuffers(1, &VBO);
		glDeleteBuffers(1, &EBO);
	}

	void Mesh::setupVAO() {
		bind();
		glVertexAttribPointer(0, 3, GL_FLOAT, false, sizeof(Vertex), (void*) 0);
		glVertexAttribPointer(1, 4, GL_FLOAT, false, sizeof(Vertex), (void*) offsetof(Vertex, color));
		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);
	}

	void Mesh::bind() {
		glBindVertexArray(VAO);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	}

	void Mesh::setVertexData(std::vector<Vertex> vertices) {
		this->vertices = vertices;
		bind();
		
		glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), vertices.data(), GL_STATIC_DRAW);
	}

	void Mesh::setIndexData(std::vector<uint32_t> indices) {
		this->indices = indices;
		bind();

		glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(uint32_t), indices.data(), GL_STATIC_DRAW);
	}

	void Mesh::draw() {
		bind();
		glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, nullptr);
	}
}

