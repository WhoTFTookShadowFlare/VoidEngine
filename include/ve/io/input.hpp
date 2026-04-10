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

		Event::EventBus<Events::EMouseMotion> onMouseMotion;
		Event::EventBus<Events::EMouseButton> onMouseButton;
		Event::EventBus<Events::EKeyButton> onKeyButton;
	};
}
