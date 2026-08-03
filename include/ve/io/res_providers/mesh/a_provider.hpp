#pragma once

#include "ve/class_db.hpp"
#include "ve/event/event.hpp"
#include "ve/event/event_bus.hpp"
#include "ve/io/gfx/vertex.hpp"
#include <cstdint>
#include <vector>

namespace VoidEngine::IO::ResourceProviders {
	class EMeshProviderChanged final : public Event::AEvent {
	public:
		static const Class ClassData;
		virtual const Class* getClass() const { return &ClassData; }
	};

	class AMeshProvider {
	public:
		Event::EventBusLegacy<EMeshProviderChanged> meshChanged;

		virtual ~AMeshProvider() {}
		virtual std::vector<VoidEngine::IO::GFX::Vertex> getVertices() = 0;
		virtual std::vector<uint32_t> getIndices() = 0;
	};
}
