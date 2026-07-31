#pragma once

#include <memory>
#include <glm/ext/vector_float2.hpp>
#include "ve/event/event.hpp"

namespace VoidEngine::IO {
	class Window;
}

namespace VoidEngine::IO::Events {
	class EMouseMotion final : public Event::AEvent {
	public:
		static const Class ClassData;
		virtual const Class* getClass() const { return &ClassData; }

		EMouseMotion(std::shared_ptr<Window> window, glm::vec2 motion, glm::vec2 relative) :
			window(window), motion(motion), relative(relative)
		{}

		const std::shared_ptr<Window> window;
		const glm::vec2 motion;
		const glm::vec2 relative;
	};

	class EMouseButton final : public Event::AEvent {
	public:
		static const Class ClassData;
		virtual const Class* getClass() const { return &ClassData; }

		EMouseButton(
			std::shared_ptr<Window> window, uint32_t mouseID, uint8_t button, bool pressed, uint8_t clicks, glm::vec2 position
		) : window(window), mouseID(mouseID), button(button), pressed(pressed), clicks(clicks), position(position)
		{}

		const std::shared_ptr<Window> window;
		const uint32_t mouseID;
		const int8_t button;
		const bool pressed;
		const uint8_t clicks;
		const glm::vec2 position;
	};

	class EKeyButton final : public Event::AEvent {
	public:
		static const Class ClassData;
		virtual const Class* getClass() const { return &ClassData; }

		EKeyButton(
			std::shared_ptr<Window> window, uint32_t keyboardID, uint32_t key, uint16_t mods, bool pressed, bool repeat
		) : window(window), keyboardID(keyboardID), key(key), modKeys(mods), pressed(pressed), repeat(repeat)
		{}

		const std::shared_ptr<Window> window;
		const uint32_t keyboardID;
		//SDL_Scancode scancode;
		const uint32_t key;
		const uint16_t modKeys;
		const bool pressed;
		const bool repeat;
	};
}
