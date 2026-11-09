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
	class AWindowEvent : public Event::AEvent {
		VE_CLASS(AWindowEvent)
	protected:
		AWindowEvent(std::shared_ptr<Window> window) : window(window) {}
	public:
		const std::shared_ptr<Window> window;

		bool isSetup() const override;
	};

	class EWindowMinimized final : public AWindowEvent {
		VE_CLASS(EWindowMinimized)
	public:
		EWindowMinimized(std::shared_ptr<Window> window) : AWindowEvent(window) {}
	};

	class EWindowRestored final : public AWindowEvent {
		VE_CLASS(EWindowRestored)
	public:
		EWindowRestored(std::shared_ptr<Window> window) : AWindowEvent(window) {}
	};

	class EWindowMaximized final : public AWindowEvent {
		VE_CLASS(EWindowMaximized)
	public:
		EWindowMaximized(std::shared_ptr<Window> window) : AWindowEvent(window) {}
	};

	class EWindowCloseRequested final : public AWindowEvent {
		VE_CLASS(EWindowCloseRequested)
	public:
		EWindowCloseRequested(std::shared_ptr<Window> window) : AWindowEvent (window) {}
	};

	class WindowCloseRequestedDefaultHandler : public Object {
		VE_CLASS(WindowCloseRequestedDefaultHandler)
	public:
		void onCloseEvent(std::shared_ptr<Object> evt);
	};

	class EWindowSizeChanged final : public AWindowEvent {
		VE_CLASS(EWindowSizeChanged)
	public:
		EWindowSizeChanged(std::shared_ptr<Window> window) : AWindowEvent(window) {}
	};

	class EWindowRepositioned final : public AWindowEvent {
		VE_CLASS(EWindowRepositioned)
	public:
		EWindowRepositioned(std::shared_ptr<Window> window) : AWindowEvent(window) {}
	};

	class EMouseEnter final : public AWindowEvent {
		VE_CLASS(EMouseEnter)
	public:
		EMouseEnter(std::shared_ptr<Window> window, bool entered) : AWindowEvent(window), entered(entered) {}
		const bool entered;
	};

	class EWindowFocus final : public AWindowEvent {
		VE_CLASS(EWindowFocus)
	public:
		EWindowFocus(std::shared_ptr<Window> window, bool focused) : AWindowEvent(window), focused(focused) {}
		const bool focused;
	};
}
