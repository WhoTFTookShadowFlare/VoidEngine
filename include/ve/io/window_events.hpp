#pragma once

#include "ve/event/event.hpp"
#include "ve/object.hpp"
#include "ve/variant.hpp"

#include <memory>
#include <vector>

namespace VoidEngine::IO {
	class Window;
}

namespace VoidEngine::IO::Events {
	class BasicWindowEvent : public Event::AEvent {
		VE_CLASS(BasicWindowEvent)
	protected:
		BasicWindowEvent(std::shared_ptr<Window> window) : window(window) {}
	public:
		const std::shared_ptr<Window> window;
	};

	class EWindowMinimized final : public BasicWindowEvent {
		VE_CLASS(EWindowMinimized)
	public:
		EWindowMinimized(std::shared_ptr<Window> window) : BasicWindowEvent(window) {}
	};

	class EWindowRestored final : public BasicWindowEvent {
		VE_CLASS(EWindowRestored)
	public:
		EWindowRestored(std::shared_ptr<Window> window) : BasicWindowEvent(window) {}
	};

	class EWindowMaximized final : public BasicWindowEvent {
		VE_CLASS(EWindowMaximized)
	public:
		EWindowMaximized(std::shared_ptr<Window> window) : BasicWindowEvent(window) {}
	};

	class EWindowCloseRequested final : public BasicWindowEvent {
		VE_CLASS(EWindowCloseRequested)
	public:
		EWindowCloseRequested(std::shared_ptr<Window> window) : BasicWindowEvent (window) {}
	};

	class WindowCloseRequestedDefaultHandler : public Object {
		VE_CLASS(WindowCloseRequestedDefaultHandler)
	public:
		void onCloseEvent(std::shared_ptr<Object> evt);
	};

	class EWindowSizeChanged final : public Event::AEvent {
		VE_CLASS(EWindowSizeChanged)
	public:
		EWindowSizeChanged(std::shared_ptr<Window> window) : window(window) {}
		const std::shared_ptr<Window> window;
	};

	class EWindowRepositioned final : public Event::AEvent {
		VE_CLASS(EWindowRepositioned)
	public:
		EWindowRepositioned(std::shared_ptr<Window> window) : window(window) {}
		const std::shared_ptr<Window> window;
	};

	class EMouseEnter final : public Event::AEvent {
		VE_CLASS(EMouseEnter)
	public:
		EMouseEnter(std::shared_ptr<Window> window, bool entered) : window(window), entered(entered) {}
		const std::shared_ptr<Window> window;
		const bool entered;
	};

	class EWindowFocus final : public Event::AEvent {
		VE_CLASS(EWindowFocus)
	public:
		EWindowFocus(std::shared_ptr<Window> window, bool focused) : window(window), focused(focused) {}
		const std::shared_ptr<Window> window;
		const bool focused;
	};
}
