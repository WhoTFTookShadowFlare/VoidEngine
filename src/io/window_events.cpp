#include "ve/io/window_events.hpp"
#include "ve/io/window.hpp"

namespace VoidEngine::IO::Events {
	const Class BasicWindowEvent::ClassData = {
		.name = "BasicWindowEvent"
	};

	const Class EWindowMinimized::ClassData = {
		.name = "EWindowMinimized"
	};

	const Class EWindowRestored::ClassData = {
		.name = "EWindowRestored"
	};

	const Class EWindowMaximized::ClassData = {
		.name = "EWindowMaximized"
	};

	const Class EWindowCloseRequested::ClassData = {
		.name = "EWindowCloseRequested"
	};

	const Class EWindowSizeChanged::ClassData = {
		.name = "EWindowSizeChanged"
	};

	const Class EWindowRepositioned::ClassData = {
		.name = "EWindowRepositioned"
	};

	const Class EMouseEnter::ClassData = {
		.name = "EMouseEnter"
	};

	const Class EWindowFocus::ClassData = {
		.name = "EWindowFocues"
	};

	void WindowCloseRequestedDefaultHandler::onEvent(EWindowCloseRequested& evt) {
		evt.window->close();
	}
}
