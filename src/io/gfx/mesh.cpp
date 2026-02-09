#include "ve/io/gfx/mesh.hpp"
#include "ve/io/gfx/mesh_provider.hpp"

namespace VoidEngine::IO::GFX {
	std::vector<Vertex>& Mesh::getVertexData() { return vertices; }
	std::vector<uint32_t>& Mesh::getIndexData() { return indices; }

	void Mesh::setMeshFromProvider(AMeshProvider& provider) {
		vertices = provider.getVertices();
		indices = provider.getIndices();
		buildMesh();
	}
}
