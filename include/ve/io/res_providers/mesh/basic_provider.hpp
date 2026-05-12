#pragma once

#include "ve/io/res_providers/mesh/a_provider.hpp"

namespace VoidEngine::IO::ResourceProviders {
	class BasicMeshProvider : public AMeshProvider {
		const std::vector<VoidEngine::IO::GFX::Vertex> vertices;
		const std::vector<uint32_t> indices;
	public:
		BasicMeshProvider(std::vector<VoidEngine::IO::GFX::Vertex> vertices, std::vector<uint32_t> indices) :
			vertices(vertices), indices(indices)
		{
		}

		std::vector<VoidEngine::IO::GFX::Vertex> getVertices() { return vertices; }
		std::vector<uint32_t> getIndices() { return indices; }
	};
}
