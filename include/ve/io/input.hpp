#pragma once

#include <memory>

#include "ve/io/input_events.hpp"
#include "ve/event/event_bus.hpp"

namespace VoidEngine::IO {
	class Input final {
	private:
		static std::shared_ptr<Input> instance;

		Input() {}
	public:
		static std::shared_ptr<Input> getInstance();

		Event::EventBus onMouseMotion = &Events::EMouseMotion::ClassData;
		Event::EventBus onMouseButton = &Events::EMouseButton::ClassData;
		Event::EventBus onKeyButton = &Events::EKeyButton::ClassData;
	};
}
