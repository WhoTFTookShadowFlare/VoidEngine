#include "ve/io/window_events.hpp"
#include "ve/io/window.hpp"

namespace VoidEngine::IO::Events {
	void WindowCloseRequestedDefaultHandler::onEvent(EWindowCloseRequested& evt) {
		evt.window->close();
	}
}
