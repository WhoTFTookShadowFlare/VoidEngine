#include "ve/io/window_events.hpp"
#include "ve/class_event_handler.hpp"
#include "ve/io/window.hpp"
#include "ve/object.hpp"
#include "ve/variant.hpp"
#include <memory>

namespace VoidEngine::IO::Events {
	const Class BasicWindowEvent::ClassData = {
		.name = "BasicWindowEvent",
		.super = &AEvent::ClassData
	};

	const Class EWindowMinimized::ClassData = {
		.name = "EWindowMinimized",
		.super = &BasicWindowEvent::ClassData
	};

	const Class EWindowRestored::ClassData = {
		.name = "EWindowRestored",
		.super = &BasicWindowEvent::ClassData
	};

	const Class EWindowMaximized::ClassData = {
		.name = "EWindowMaximized",
		.super = &BasicWindowEvent::ClassData
	};

	const Class EWindowCloseRequested::ClassData = {
		.name = "EWindowCloseRequested",
		.super = &BasicWindowEvent::ClassData
	};

	const Class EWindowSizeChanged::ClassData = {
		.name = "EWindowSizeChanged",
		.super = &AEvent::ClassData
	};

	const Class EWindowRepositioned::ClassData = {
		.name = "EWindowRepositioned",
		.super = &AEvent::ClassData
	};

	const Class EMouseEnter::ClassData = {
		.name = "EMouseEnter",
		.super = &AEvent::ClassData
	};

	const Class EWindowFocus::ClassData = {
		.name = "EWindowFocues",
		.super = &AEvent::ClassData
	};

	const Class WindowCloseRequestedDefaultHandler::ClassData = {
		.name = "WindowCloseRequestedDefaultHandler",
		.super = &Object::ClassData,
		.eventHandlers = {
			new NativeEventHandler(&EWindowCloseRequested::ClassData, &WindowCloseRequestedDefaultHandler::onCloseEvent)
		}
	};

	void WindowCloseRequestedDefaultHandler::onCloseEvent(std::shared_ptr<Object> evt) {
		auto winEvt = std::static_pointer_cast<EWindowCloseRequested>(evt);
		winEvt->window->close();
	}
}
