#include <ve/io/joystick.hpp>
#include "_joystick_internal.hpp"

#include <ve/class_event_bus.hpp>
#include <ve/class_property.hpp>

#include <SDL3/SDL_joystick.h>

namespace VoidEngine::IO {
	const Class AJoystick::ClassData = {
		.name = "AJoystick",
		.super = &Object::ClassData,
		.properties = {
			new NativeProperty("name", &AJoystick::scr_getName)
		},
		.eventBusses = {
			new NativeEventBus(&Events::EJoystickDisconnected::ClassData, &AJoystick::onDisconnect),
			new NativeEventBus(&Events::EJoystickButton::ClassData, &AJoystick::onButton),
			new NativeEventBus(&Events::EJoystickAxis::ClassData, &AJoystick::onAxis),
			new NativeEventBus(&Events::EJoystickHat::ClassData, &AJoystick::onHat),
		}
	};

	Variant AJoystick::scr_getName(void) const {
		return getName();
	}

	AJoystick::AJoystick() {
		internal = new JoystickInternal;
	}

	AJoystick::~AJoystick() {
		delete internal;
	}

	std::string AJoystick::getName() const {
		return SDL_GetJoystickName(internal->ctrl);
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
