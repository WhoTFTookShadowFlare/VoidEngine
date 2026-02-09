#pragma once

#include "ve/io/gfx/vertex.hpp"
#include <cstdint>
#include <vector>

namespace VoidEngine::IO::GFX {
	class AMeshProvider {
	public:
		virtual ~AMeshProvider() {}
		virtual std::vector<Vertex> getVertices() = 0;
		virtual std::vector<uint32_t> getIndices() = 0;
	};

	class BasicMeshProvider : public AMeshProvider {
		std::vector<Vertex> vertices;
		std::vector<uint32_t> indices;
	public:
		BasicMeshProvider(std::vector<Vertex> vertices, std::vector<uint32_t> indices) :
			vertices(vertices), indices(indices)
		{}

		std::vector<Vertex> getVertices() { return vertices; }
		std::vector<uint32_t> getIndices() { return indices; }
	};
}

