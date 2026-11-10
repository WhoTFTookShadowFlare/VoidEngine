#pragma once

#include <ve/object.hpp>
#include <ve/io/input_events.hpp>
#include <ve/event/event_bus.hpp>

namespace VoidEngine {
	class Engine;
}

namespace VoidEngine::IO {
	struct JoystickInternal;
	class AJoystick : public Object {
		VE_CLASS(AJoystick)
		friend class ::VoidEngine::Engine;
	private:
		JoystickInternal* internal = nullptr;
	protected:
		AJoystick();
	public:
		virtual ~AJoystick();

		virtual bool isButtonDown() = 0;

		Event::EventBus onDisconnect = &Events::EJoystickDisconnected::ClassData;
		Event::EventBus onButton = &Events::EJoystickButton::ClassData;
	};

	class HardwareJoystick final : public AJoystick {
		VE_CLASS(HardwareJoystick)
		friend class ::VoidEngine::Engine;
	private:
		
		HardwareJoystick() = default;
		// Internal only constructor
		static std::shared_ptr<HardwareJoystick> create();
	public:
		~HardwareJoystick();

		virtual bool isButtonDown();
	};

	class SoftwareJoystick final : public AJoystick {
		VE_CLASS(SoftwareJoystick)
	private:
		SoftwareJoystick() = default;
	public:
		static std::shared_ptr<SoftwareJoystick> create();
		~SoftwareJoystick();

		virtual bool isButtonDown();
	};
}
