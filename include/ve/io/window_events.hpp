#pragma once

#include "ve/event/event_listener.hpp"

#include <memory>

namespace VoidEngine::IO {
	class Window;
}

namespace VoidEngine::IO::Events {
	class BasicWindowEvent {
	protected:
		BasicWindowEvent(std::shared_ptr<Window> window) : window(window) {}
	public:
		const std::shared_ptr<Window> window;
	};

	class EWindowMinimized final : public BasicWindowEvent {
	public:
		EWindowMinimized(std::shared_ptr<Window> window) : BasicWindowEvent(window) {}
	};

	class EWindowRestored final : public BasicWindowEvent {
	public:
		EWindowRestored(std::shared_ptr<Window> window) : BasicWindowEvent(window) {}
	};

	class EWindowMaximized final : public BasicWindowEvent {
	public:
		EWindowMaximized(std::shared_ptr<Window> window) : BasicWindowEvent(window) {}
	};

	class EWindowCloseRequested final : public BasicWindowEvent {
	public:
		EWindowCloseRequested(std::shared_ptr<Window> window) : BasicWindowEvent (window) {}
	};

	class WindowCloseRequestedDefaultHandler : public Event::IEventListener<EWindowCloseRequested> {
	public:
		void onEvent(EWindowCloseRequested& evt);
	};

	class EWindowSizeChanged final {
	public:
		EWindowSizeChanged(std::shared_ptr<Window> window) : window(window) {}
		const std::shared_ptr<Window> window;
	};

	class EWindowRepositioned final {
	public:
		EWindowRepositioned(std::shared_ptr<Window> window) : window(window) {}
		const std::shared_ptr<Window> window;
	};

	class EMouseEnter final {
	public:
		EMouseEnter(std::shared_ptr<Window> window, bool entered) : window(window), entered(entered) {}
		const std::shared_ptr<Window> window;
		const bool entered;
	};

	class EWindowFocus final {
	public:
		EWindowFocus(std::shared_ptr<Window> window, bool focused) : window(window), focused(focused) {}
		const std::shared_ptr<Window> window;
		const bool focused;
	};
}
