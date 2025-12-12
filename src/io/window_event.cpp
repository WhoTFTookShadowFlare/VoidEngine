#include "io/window_event.hpp"
#include "io/window.hpp"
#include <glm/ext/vector_float2.hpp>
#include <glm/ext/vector_int2.hpp>

namespace VoidEngine::IO::Events {
	MouseMoved::MouseMoved(Window* window, glm::vec2 mousePos, glm::vec2 relative) {
		if(window == nullptr) return;
		this->window = window;
		this->mousePos = mousePos;
		this->relative = relative;
	}
}
