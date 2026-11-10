#include "ve/event/event.hpp"
#include "ve/class_db.hpp"
#include "ve/class_methods.hpp"
#include "ve/class_constructor.hpp"

namespace VoidEngine::Event {
	const Class AEvent::ClassData = {
		.name = "AEvent",
		.super = &Object::ClassData,
		.methods = {
			new NativeMethod("isSetup", &AEvent::scr_isSetup)
		},
		.constructor = new NativeConstructor(&AEvent::create)
	};

	std::shared_ptr<AEvent> AEvent::create() {
		return std::shared_ptr<AEvent>(new AEvent);
	}
}
