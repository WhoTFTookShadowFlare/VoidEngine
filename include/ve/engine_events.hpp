#pragma once

#include "ve/event/event.hpp"

namespace VoidEngine::Events {
	class EQuitEvent final : public Event::AEvent {
	public:
		static const Class ClassData;
		virtual const Class* getClass() const { return &ClassData; }
	};
	
	class EScreenLayoutChangedEvent final : public Event::AEvent {
	public:
		static const Class ClassData;
		virtual const Class* getClass() const { return &ClassData; }
	};
}
