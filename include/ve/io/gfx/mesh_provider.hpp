#pragma once

#include "ve/event/event_bus.hpp"
#include "ve/io/gfx/vertex.hpp"
#include <cstdint>
#include <vector>

namespace VoidEngine::IO::GFX {
	class EMeshProviderChanged final {};

	class AMeshProvider {
	public:
		Event::EventBus<EMeshProviderChanged> meshChanged;

		virtual ~AMeshProvider() {}
		virtual std::vector<Vertex> getVertices() = 0;
		virtual std::vector<uint32_t> getIndices() = 0;
	};

	class BasicMeshProvider : public AMeshProvider {
		const std::vector<Vertex> vertices;
		const std::vector<uint32_t> indices;
	public:
		BasicMeshProvider(std::vector<Vertex> vertices, std::vector<uint32_t> indices) :
			vertices(vertices), indices(indices)
		{}

		std::vector<Vertex> getVertices() { return vertices; }
		std::vector<uint32_t> getIndices() { return indices; }
	};
}

