#include "ve/io/input_events.hpp"
#include "ve/event/event.hpp"

namespace VoidEngine::IO::Events {
	const Class EMouseMotion::ClassData = {
		.name = "EMouseMotion",
		.super = &Event::AEvent::ClassData
	};

	const Class EMouseButton::ClassData = {
		.name = "EMouseButton",
		.super = &Event::AEvent::ClassData
	};

	const Class EKeyButton::ClassData = {
		.name = "EKeyButton",
		.super = &Event::AEvent::ClassData
	};
}
