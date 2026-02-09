#pragma once

#include "ve/io/gfx/mesh_provider.hpp"
#include "ve/io/gfx/vertex.hpp"
#include <cstdint>
#include <vector>

namespace VoidEngine::IO::GFX {
	class GraphicsProgram;
	class Mesh {
		friend class GraphicsProgram;
		std::vector<Vertex> vertices;
		std::vector<uint32_t> indices;
		
		virtual void draw() = 0;
	protected:
		virtual void buildMesh() = 0;
	public:
		virtual ~Mesh() {}

		std::vector<Vertex>& getVertexData();
		std::vector<uint32_t>& getIndexData();

		void setMeshFromProvider(AMeshProvider&);
	};
}

