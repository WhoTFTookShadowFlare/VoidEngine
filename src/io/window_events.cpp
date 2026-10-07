#include "ve/io/window_events.hpp"
#include "ve/class_event_handler.hpp"
#include "ve/io/window.hpp"
#include "ve/object.hpp"
#include "ve/variant.hpp"
#include <memory>

namespace VoidEngine::IO::Events {
	const Class AWindowEvent::ClassData = {
		.name = "AWindowEvent",
		.super = &AEvent::ClassData
	};

	bool AWindowEvent::isSetup() const {
		return window != nullptr;
	}

	const Class EWindowMinimized::ClassData = {
		.name = "EWindowMinimized",
		.super = &AWindowEvent::ClassData,
		.flags = ClassFlags::FINAL
	};

	const Class EWindowRestored::ClassData = {
		.name = "EWindowRestored",
		.super = &AWindowEvent::ClassData,
		.flags = ClassFlags::FINAL
	};

	const Class EWindowMaximized::ClassData = {
		.name = "EWindowMaximized",
		.super = &AWindowEvent::ClassData,
		.flags = ClassFlags::FINAL
	};

	const Class EWindowCloseRequested::ClassData = {
		.name = "EWindowCloseRequested",
		.super = &AWindowEvent::ClassData,
		.flags = ClassFlags::FINAL
	};

	const Class EWindowSizeChanged::ClassData = {
		.name = "EWindowSizeChanged",
		.super = &AWindowEvent::ClassData,
		.flags = ClassFlags::FINAL
	};

	const Class EWindowRepositioned::ClassData = {
		.name = "EWindowRepositioned",
		.super = &AWindowEvent::ClassData,
		.flags = ClassFlags::FINAL
	};

	const Class EMouseEnter::ClassData = {
		.name = "EMouseEnter",
		.super = &AWindowEvent::ClassData,
		.flags = ClassFlags::FINAL
	};

	const Class EWindowFocus::ClassData = {
		.name = "EWindowFocues",
		.super = &AWindowEvent::ClassData,
		.flags = ClassFlags::FINAL
	};

	const Class WindowCloseRequestedDefaultHandler::ClassData = {
		.name = "WindowCloseRequestedDefaultHandler",
		.super = &Object::ClassData,
		.eventHandlers = {
			new NativeEventHandler(&EWindowCloseRequested::ClassData, &WindowCloseRequestedDefaultHandler::onCloseEvent)
		},
		.flags = ClassFlags::FINAL
	};

	void WindowCloseRequestedDefaultHandler::onCloseEvent(std::shared_ptr<Object> evt) {
		auto winEvt = std::static_pointer_cast<EWindowCloseRequested>(evt);
		winEvt->window->close();
	}
}
