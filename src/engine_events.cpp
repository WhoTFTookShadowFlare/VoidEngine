#include "ve/engine_events.hpp"
#include "ve/event/event.hpp"

namespace VoidEngine::Events {
	const Class EQuitEvent::ClassData = {
		.name = "EQuitEvent",
		.super = &Event::AEvent::ClassData
	};

	const Class EScreenLayoutChangedEvent::ClassData = {
		.name = "EScreenLayoutChanged",
		.super = &Event::AEvent::ClassData
	};
}
