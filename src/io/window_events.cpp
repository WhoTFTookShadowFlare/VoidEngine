#include "ve/io/window_events.hpp"
#include "ve/class_methods.hpp"
#include "ve/io/window.hpp"
#include "ve/variant.hpp"
#include <memory>
#include <vector>

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

	const Class WindowCloseRequestedDefaultHandler::ClassData = {
		.name = "WindowCloseRequestedDefaultHandler",
		.methods = {
			new Method("onCloseEvent", &WindowCloseRequestedDefaultHandler::onCloseEvent)
		}
	};

	Variant WindowCloseRequestedDefaultHandler::onCloseEvent(std::vector<Variant> evt) {
		auto winEvt = std::static_pointer_cast<Events::EWindowCloseRequested>(evt[0].asObject().value());
		winEvt->window->close();
		return nullptr;
	}
}
