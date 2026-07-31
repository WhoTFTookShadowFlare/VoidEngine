#include "ve/engine_events.hpp"

namespace VoidEngine::Events {
	const Class EQuitEvent::ClassData = {
		.name = "EQuitEvent"
	};

	const Class EScreenLayoutChangedEvent::ClassData = {
		.name = "EScreenLayoutChanged"
	};
}
