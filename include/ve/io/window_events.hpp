#pragma once

#include "ve/event/event.hpp"
#include "ve/event/event_listener.hpp"
#include "ve/variant.hpp"

#include <memory>
#include <vector>

namespace VoidEngine::IO {
	class Window;
}

namespace VoidEngine::IO::Events {
	class BasicWindowEvent : public Event::AEvent {
	protected:
		BasicWindowEvent(std::shared_ptr<Window> window) : window(window) {}
	public:
		static const Class ClassData;
		virtual const Class* getClass() const { return &ClassData; }
		
		const std::shared_ptr<Window> window;
	};

	class EWindowMinimized final : public BasicWindowEvent {
	public:
		static const Class ClassData;
		virtual const Class* getClass() const { return &ClassData; }
		
		EWindowMinimized(std::shared_ptr<Window> window) : BasicWindowEvent(window) {}
	};

	class EWindowRestored final : public BasicWindowEvent {
	public:
		static const Class ClassData;
		virtual const Class* getClass() const { return &ClassData; }
		
		EWindowRestored(std::shared_ptr<Window> window) : BasicWindowEvent(window) {}
	};

	class EWindowMaximized final : public BasicWindowEvent {
	public:
		static const Class ClassData;
		virtual const Class* getClass() const { return &ClassData; }
		
		EWindowMaximized(std::shared_ptr<Window> window) : BasicWindowEvent(window) {}
	};

	class EWindowCloseRequested final : public BasicWindowEvent {
	public:
		static const Class ClassData;
		virtual const Class* getClass() const { return &ClassData; }
		
		EWindowCloseRequested(std::shared_ptr<Window> window) : BasicWindowEvent (window) {}
	};

	class WindowCloseRequestedDefaultHandler : public Object {
	public:
		static const Class ClassData;
		virtual const Class* getClass() const { return &ClassData; }
		Variant onCloseEvent(std::vector<Variant> evt);
	};

	class EWindowSizeChanged final : public Event::AEvent {
	public:
		static const Class ClassData;
		virtual const Class* getClass() const { return &ClassData; }
		
		EWindowSizeChanged(std::shared_ptr<Window> window) : window(window) {}
		const std::shared_ptr<Window> window;
	};

	class EWindowRepositioned final : public Event::AEvent {
	public:
		static const Class ClassData;
		virtual const Class* getClass() const { return &ClassData; }
		
		EWindowRepositioned(std::shared_ptr<Window> window) : window(window) {}
		const std::shared_ptr<Window> window;
	};

	class EMouseEnter final : public Event::AEvent {
	public:
		static const Class ClassData;
		virtual const Class* getClass() const { return &ClassData; }
		
		EMouseEnter(std::shared_ptr<Window> window, bool entered) : window(window), entered(entered) {}
		const std::shared_ptr<Window> window;
		const bool entered;
	};

	class EWindowFocus final : public Event::AEvent {
	public:
		static const Class ClassData;
		virtual const Class* getClass() const { return &ClassData; }
		
		EWindowFocus(std::shared_ptr<Window> window, bool focused) : window(window), focused(focused) {}
		const std::shared_ptr<Window> window;
		const bool focused;
	};
}
