#include "ve/object.hpp"

#include "ve/class_db.hpp"
#include <print>

namespace VoidEngine {
	const Class Object::ClassData = {
		.name = "Object",
		.super = nullptr
	};

	std::shared_ptr<Scripts::AObjectScript> Object::getScript() const {
		return script;
	}

	void Object::setScript(std::shared_ptr<Scripts::AObjectScript> value) {
		if(value->getClass() == nullptr || !value->getClass()->instanceOf(getClass())) {
			std::println("[ERR] Cannot set script that does not inherit the class");
			return;
		}
		
		script = value;
	}
}
