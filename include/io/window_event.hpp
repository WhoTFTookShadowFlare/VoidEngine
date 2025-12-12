#pragma once

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
}
