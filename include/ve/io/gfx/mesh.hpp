#pragma once

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
	public:
		virtual ~Mesh() {}

		void setVertexData(std::vector<Vertex> data);
		void setIndexData(std::vector<uint32_t> data);

		std::vector<Vertex>& getVertexData();
		std::vector<uint32_t>& getIndexData();

		virtual void buildMesh() = 0;
	};
}

