#include "ve/io/gfx/mesh.hpp"

namespace VoidEngine::IO::GFX {
	void Mesh::setVertexData(std::vector<Vertex> data) { vertices = data; }
	void Mesh::setIndexData(std::vector<uint32_t> data) { indices = data; }

	std::vector<Vertex>& Mesh::getVertexData() { return vertices; }
	std::vector<uint32_t>& Mesh::getIndexData() { return indices; }
}
