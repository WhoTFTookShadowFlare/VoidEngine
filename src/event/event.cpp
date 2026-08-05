#include "ve/event/event.hpp"
#include "ve/class_db.hpp"

namespace VoidEngine::Event {
	const Class AEvent::ClassData = {
		.name = "AEvent",
		.super = &Object::ClassData
	};
}
