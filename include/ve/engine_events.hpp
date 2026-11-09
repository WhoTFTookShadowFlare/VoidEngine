#pragma once

#include "ve/event/event.hpp"
#include "ve/object.hpp"

namespace VoidEngine::Events {
	class EQuitEvent final : public Event::AEvent {
		VE_CLASS(EQuitEvent)
	public:
		bool isSetup() const override { return true; }
	};
	
	class EScreenLayoutChangedEvent final : public Event::AEvent {
		VE_CLASS(EScreenLayoutChangedEvent)
	public:
		bool isSetup() const override { return true; }
	};
}
