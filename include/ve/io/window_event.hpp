#pragma once

#include <cstdint>
#include <glm/ext/vector_float2.hpp>
#include <glm/ext/vector_int2.hpp>

namespace VoidEngine::IO {
	class Window;
}

namespace VoidEngine::IO::Events {
	class WindowCloseRequested {	};

	class MouseMoved {
		Window* window;
		glm::vec2 mousePos;
		glm::vec2 relative;
	public:
		MouseMoved(Window* window, glm::vec2 mousePos, glm::vec2);

		glm::vec2 getMousePosition() const {
			return mousePos;
		}

		glm::vec2 getMouseRelative() const {
			return relative;
		}
	};

	class MouseButtonPressed {
		Window* window = nullptr;
		uint8_t clicks = 0, button = 0;
		bool pressed = false;
	public:
		MouseButtonPressed(Window* window, uint8_t clicks, uint8_t button, bool pressed) :
			window(window), clicks(clicks), button(button) {	}

		uint8_t getClicks() const { return clicks; }
		uint8_t getButton() const { return button; }
		bool wasPressed() const { return pressed; }
	};
}
