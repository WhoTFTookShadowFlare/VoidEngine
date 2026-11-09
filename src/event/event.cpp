#include "ve/event/event.hpp"
#include "ve/class_db.hpp"
#include "ve/class_methods.hpp"

namespace VoidEngine::Event {
	const Class AEvent::ClassData = {
		.name = "AEvent",
		.super = &Object::ClassData,
		.methods = {
			new NativeMethod("isSetup", &AEvent::scr_isSetup)
		},
	};
}
