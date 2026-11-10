#include "ve/io/input_events.hpp"
#include "ve/event/event.hpp"

#include <ve/io/joystick.hpp>

#include "ve/class_property.hpp"
#include "ve/class_constructor.hpp"

namespace VoidEngine::IO::Events {
	const Class EMouseMotion::ClassData = {
		.name = "EMouseMotion",
		.super = &Event::AEvent::ClassData,
		.flags = ClassFlags::FINAL
	};

	const Class EMouseButton::ClassData = {
		.name = "EMouseButton",
		.super = &Event::AEvent::ClassData,
		.flags = ClassFlags::FINAL
	};

	const Class EKeyButton::ClassData = {
		.name = "EKeyButton",
		.super = &Event::AEvent::ClassData,
		.flags = ClassFlags::FINAL
	};

	const Class AJoystickEvent::ClassData = {
		.name = "AJoystickEvent",
		.super = &Event::AEvent::ClassData,
		.properties = {
			new NativeProperty("joystick", &AJoystickEvent::scr_getJoystick)
		}
	};

	Variant AJoystickEvent::scr_getJoystick(void) const {
		return Variant(getJoystick());
	}

	std::shared_ptr<AJoystick> AJoystickEvent::getJoystick() const {
		return joystick;
	}

	bool AJoystickEvent::isSetup() const {
		return joystick != nullptr;
	}

	const Class EJoystickConnected::ClassData = {
		.name = "EJoystickConnected",
		.super = &AJoystickEvent::ClassData,
		.constructor = new NativeConstructor(&EJoystickConnected::create),
		.flags = ClassFlags::FINAL
	};

	std::shared_ptr<EJoystickConnected> EJoystickConnected::create() {
		return std::shared_ptr<EJoystickConnected>(new EJoystickConnected);
	}

	const Class EJoystickDisconnected::ClassData = {
		.name = "EJoystickDisconnected",
		.super = &AJoystickEvent::ClassData,
		.constructor = new NativeConstructor(&EJoystickDisconnected::create),
		.flags = ClassFlags::FINAL
	};

	std::shared_ptr<EJoystickDisconnected> EJoystickDisconnected::create() {
		return std::shared_ptr<EJoystickDisconnected>(new EJoystickDisconnected);
	}
	
	const Class EJoystickButton::ClassData = {
		.name = "EJoystickButton",
		.super = &AJoystickEvent::ClassData,
		.properties = {
			new NativeProperty("button", &EJoystickButton::scr_getButton),
			new NativeProperty("pressed", &EJoystickButton::scr_wasPressed)
		},
		.constructor = new NativeConstructor(&EJoystickButton::create),
		.flags = ClassFlags::FINAL
	};

	Variant EJoystickButton::scr_getButton(void) const {
		return getButton();
	}

	Variant EJoystickButton::scr_wasPressed(void) const {
		return wasPressed();
	}

	std::shared_ptr<EJoystickButton> EJoystickButton::create() {
		return std::shared_ptr<EJoystickButton>(new EJoystickButton);
	}

	uint8_t EJoystickButton::getButton() const {
		return button;
	}
	
	bool EJoystickButton::wasPressed() const {
		return pressed;
	}

	const Class EJoystickAxis::ClassData = {
		.name = "EJoystickAxis",
		.super = &AJoystickEvent::ClassData,
		.properties = {
			new NativeProperty("axis", &EJoystickAxis::scr_getAxis),
			new NativeProperty("value", &EJoystickAxis::scr_getValue)
		},
		.constructor = new NativeConstructor(&EJoystickAxis::create),
		.flags = ClassFlags::FINAL
	};

	Variant EJoystickAxis::scr_getAxis(void) const {
		return getAxis();
	}

	Variant EJoystickAxis::scr_getValue(void) const {
		return getValue();
	}

	std::shared_ptr<EJoystickAxis> EJoystickAxis::create() {
		return std::shared_ptr<EJoystickAxis>(new EJoystickAxis);
	}

	uint8_t EJoystickAxis::getAxis() const {
		return axis;
	}

	float EJoystickAxis::getValue() const {
		return value;
	}

	const Class EJoystickHat::ClassData = {
		.name = "EJoystickHat",
		.super = &AJoystickEvent::ClassData,
		.properties = {
			new NativeProperty("hat", &EJoystickHat::scr_getHat),
			new NativeProperty("value", &EJoystickHat::scr_getValue),
		},
		.constructor = new NativeConstructor(&EJoystickHat::create)
	};

	Variant EJoystickHat::scr_getHat(void) const {
		return getHat();
	}

	Variant EJoystickHat::scr_getValue(void) const {
		return getValue();
	}

	std::shared_ptr<EJoystickHat> EJoystickHat::create() {
		return std::shared_ptr<EJoystickHat>(new EJoystickHat);
	}

	uint8_t EJoystickHat::getHat() const {
		return hat;
	}

	uint8_t EJoystickHat::getValue() const {
		return value;
	}
}
