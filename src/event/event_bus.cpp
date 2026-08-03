#include "ve/event/event_bus.hpp"
#include "ve/class_db.hpp"
#include "ve/event/event.hpp"
#include <algorithm>
#include <memory>

namespace VoidEngine::Event {
	EventBus::EventBus(const Class* eventClass) {
		// TODO: Ensure that the provided class is of type AEvent
		this->eventClass = eventClass;
	}
	
	void EventBus::addHandler(std::shared_ptr<EventHandler> handler) {
		handlers.push_back(handler);
	}

	void EventBus::removeHandler(std::shared_ptr<EventHandler> handler) {
		handlers.resize(std::distance(
			handlers.begin(),
			std::remove_if(handlers.begin(), handlers.end(), [](const auto& iter) {
				return iter->isValid();
			})
		));
	}

	bool EventBus::hasHandler(std::shared_ptr<EventHandler> handler) const {
		const auto idx = std::find_if(handlers.cbegin(), handlers.cend(), [&handler](const auto& iter) {
			return *iter == *handler;
		});
		return idx != handlers.cend();
	}

	void EventBus::fireEvent(std::shared_ptr<AEvent> event) const {
		if(event == nullptr) return;
		if(!event->getClass()->instanceOf(eventClass)) {
			std::println("[ERR] Provided event ({}) is not of type {}", event->getClass()->getName(), eventClass->getName());
			return;
		}
		
		std::for_each(handlers.cbegin(), handlers.cend(), [&](const auto& handler) {
			handler->handle(event);
		});
	}
}
