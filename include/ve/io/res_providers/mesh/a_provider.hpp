#pragma once

#include "ve/class_db.hpp"
#include "ve/event/event.hpp"
#include "ve/event/event_bus.hpp"
#include "ve/io/gfx/vertex.hpp"
#include "ve/object.hpp"
#include <cstdint>
#include <vector>

namespace VoidEngine::IO::ResourceProviders {
	class EMeshProviderChanged final : public Event::AEvent {
		VE_CLASS(EMeshProviderChanged)
	public:
	};

	class AMeshProvider {
	public:
		Event::EventBus meshChanged = &EMeshProviderChanged::ClassData;

		virtual ~AMeshProvider() {}
		virtual std::vector<VoidEngine::IO::GFX::Vertex> getVertices() = 0;
		virtual std::vector<uint32_t> getIndices() = 0;
	};
}
