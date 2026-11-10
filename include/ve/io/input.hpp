#pragma once

#include <memory>

#include "ve/io/input_events.hpp"
#include "ve/event/event_bus.hpp"
#include "ve/io/joystick.hpp"

namespace VoidEngine::IO {
	class Input final {
		friend class ::VoidEngine::Engine;
	private:
		static std::shared_ptr<Input> instance;

		Input() = default;

		std::vector<std::shared_ptr<AJoystick>> joysticks;
	public:
		static std::shared_ptr<Input> getInstance();

		Event::EventBus onMouseMotion = &Events::EMouseMotion::ClassData;
		Event::EventBus onMouseButton = &Events::EMouseButton::ClassData;
		Event::EventBus onKeyButton = &Events::EKeyButton::ClassData;
		Event::EventBus onJoystickConnected = &Events::EJoystickConnected::ClassData;

		std::vector<std::shared_ptr<AJoystick>> getJoysticks();
	};
}
