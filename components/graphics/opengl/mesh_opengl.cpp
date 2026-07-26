#include "mesh_opengl.hpp"
#include "ve/io/gfx/vertex.hpp"
#include <cstddef>
#include <cstdint>
#include <glbinding/gl/enum.h>
#include <glbinding/gl/functions.h>
#include <glbinding/gl46core/gl.h>
#include <vector>

namespace VoidEngine::IO::GFX::OpenGL {
	using namespace gl;
	
	GLMesh::GLMesh() {
		glGenBuffers(1, &VBO);
	}

	GLMesh::~GLMesh() {
		glDeleteBuffers(1, &VBO);
	}

	void GLMesh::buildMesh() {
		auto provider = getMeshProvider();
		auto vertices = provider->getVertices();
		auto indices = provider->getIndices();

		std::vector<Vertex> built(indices.size());

		for(uint32_t idx = 0; idx < indices.size(); idx++) built[idx] = vertices[indices[idx]];

		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * built.size(), built.data(), GL_STATIC_DRAW);
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		builtVtxCount = built.size();
	}

	void GLMesh::draw() {
		glBindBuffer(GL_ARRAY_BUFFER, VBO);

		glVertexAttribPointer(0, 3, GL_FLOAT, false, sizeof(Vertex), (void*) 0);
		glVertexAttribPointer(1, 4, GL_FLOAT, false, sizeof(Vertex), (void*) offsetof(Vertex, color));
		glVertexAttribPointer(2, 2, GL_FLOAT, false, sizeof(Vertex), (void*) offsetof(Vertex, UV));
		glVertexAttribPointer(3, 3, GL_FLOAT, false, sizeof(Vertex), (void*) offsetof(Vertex, normal));
		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);
		glEnableVertexAttribArray(2);
		glEnableVertexAttribArray(3);
		glDrawArrays(GL_TRIANGLES, 0, builtVtxCount);

		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}
}

