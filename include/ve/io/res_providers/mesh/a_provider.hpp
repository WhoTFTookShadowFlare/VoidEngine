#pragma once

#include "ve/event/event_bus.hpp"
#include "ve/io/gfx/vertex.hpp"
#include <cstdint>
#include <vector>

namespace VoidEngine::IO::ResourceProviders {
	class EMeshProviderChanged final {};

	class AMeshProvider {
	public:
		Event::EventBus<EMeshProviderChanged> meshChanged;

		virtual ~AMeshProvider() {}
		virtual std::vector<VoidEngine::IO::GFX::Vertex> getVertices() = 0;
		virtual std::vector<uint32_t> getIndices() = 0;
	};
}
