#pragma once

#include <memory>
#include <glm/ext/vector_float2.hpp>
#include "ve/event/event.hpp"
#include "ve/io/window_events.hpp"
#include "ve/object.hpp"

namespace VoidEngine {
	class Engine;
}

namespace VoidEngine::IO {
	class Window;
	class AJoystick;
}

namespace VoidEngine::IO::Events {
	class EMouseMotion final : public AWindowEvent {
		VE_CLASS(EMouseMotion)
	public:
		EMouseMotion(std::shared_ptr<Window> window, glm::vec2 motion, glm::vec2 relative) :
			AWindowEvent(window), motion(motion), relative(relative)
		{}

		const glm::vec2 motion;
		const glm::vec2 relative;
	};

	class EMouseButton final : public AWindowEvent {
		VE_CLASS(EMouseButton)
	public:
		EMouseButton(
			std::shared_ptr<Window> window, uint32_t mouseID, uint8_t button, bool pressed, uint8_t clicks, glm::vec2 position
		) : AWindowEvent(window), mouseID(mouseID), button(button), pressed(pressed), clicks(clicks), position(position)
		{}

		const uint32_t mouseID;
		const int8_t button;
		const bool pressed;
		const uint8_t clicks;
		const glm::vec2 position;
	};

	class EKeyButton final : public AWindowEvent {
		VE_CLASS(EKeyButton)
	public:
		EKeyButton(
			std::shared_ptr<Window> window, uint32_t keyboardID, uint32_t key, uint16_t mods, bool pressed, bool repeat
		) : AWindowEvent(window), keyboardID(keyboardID), key(key), modKeys(mods), pressed(pressed), repeat(repeat)
		{}

		const uint32_t keyboardID;
		//SDL_Scancode scancode;
		const uint32_t key;
		const uint16_t modKeys;
		const bool pressed;
		const bool repeat;
	};

	class AJoystickEvent : public Event::AEvent {
		friend class ::VoidEngine::Engine;
		VE_CLASS(AJoystickEvent)
	private:
		std::shared_ptr<AJoystick> joystick = nullptr;

		Variant scr_getJoystick(void) const;

	protected:
		AJoystickEvent() = default;
	public:
		std::shared_ptr<AJoystick> getJoystick() const;

		bool isSetup() const;
	};

	class EJoystickConnected final : public AJoystickEvent {
		friend class ::VoidEngine::Engine;
		VE_CLASS(EJoystickConnected)
	private:
		EJoystickConnected() = default;

	public:
		static std::shared_ptr<EJoystickConnected> create();
	};

	class EJoystickDisconnected final : public AJoystickEvent {
		friend class ::VoidEngine::Engine;
		VE_CLASS(EJoystickDisconnected)
	private:
		EJoystickDisconnected() = default;
	public:
		static std::shared_ptr<EJoystickDisconnected> create();
	};

	class EJoystickButton final : public AJoystickEvent {
		friend class ::VoidEngine::Engine;
		VE_CLASS(EJoystickButton)
	private:
		EJoystickButton() = default;

		uint8_t button = 0;
		bool pressed = false;

		Variant scr_getButton(void) const;
		Variant scr_wasPressed(void) const;
	public:
		static std::shared_ptr<EJoystickButton> create();

		uint8_t getButton() const;
		bool wasPressed() const;
	};
}
