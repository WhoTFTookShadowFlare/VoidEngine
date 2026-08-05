#pragma once

#include "ve/event/event.hpp"
#include "ve/event/event_bus.hpp"
#include "ve/object.hpp"
#include <cstdint>
#include <glm/ext/vector_int2.hpp>
#include <vector>

namespace VoidEngine::IO::ResourceProviders {
	class ETextureChanged final : public Event::AEvent {
		VE_CLASS(ETextureChanged)
	public:
	};

	class ATextureProvider {
	public:
		virtual ~ATextureProvider() {}

		virtual glm::ivec2 getSize() = 0;
		virtual std::vector<uint8_t> getData() = 0;

		Event::EventBus onTextureChange = &ETextureChanged::ClassData;
	};
}
