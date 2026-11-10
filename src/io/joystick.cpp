#include <ve/io/joystick.hpp>
#include "_joystick_internal.hpp"

#include <ve/class_event_bus.hpp>

namespace VoidEngine::IO {
	const Class AJoystick::ClassData = {
		.name = "AJoystick",
		.super = &Object::ClassData,
		.eventBusses = {
			new NativeEventBus(&Events::EJoystickDisconnected::ClassData, &AJoystick::onDisconnect),
			new NativeEventBus(&Events::EJoystickButton::ClassData, &AJoystick::onButton),
		}
	};

	AJoystick::AJoystick() {
		internal = new JoystickInternal;
	}

	AJoystick::~AJoystick() {
		delete internal;
	}

	const Class HardwareJoystick::ClassData = {
		.name = "HardwareJoystick",
		.super = &AJoystick::ClassData
	};

	std::shared_ptr<HardwareJoystick> HardwareJoystick::create() {
		return std::shared_ptr<HardwareJoystick>(new HardwareJoystick);
	}

	HardwareJoystick::~HardwareJoystick() {

	}

	bool HardwareJoystick::isButtonDown() {
		return false;
	}

	const Class SoftwareJoystick::ClassData = {
		.name = "SoftwareJoystick",
		.super = &AJoystick::ClassData
	};
}
