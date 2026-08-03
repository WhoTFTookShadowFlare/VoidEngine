#pragma once

#include <algorithm>
#include <memory>
#include <print>
#include <vector>
#include "ve/class_db.hpp"
#include "ve/event/event.hpp"
#include "ve/event/event_handler.hpp"
#include "ve/event/event_listener.hpp"

namespace VoidEngine::Event {
	class EventBus final {
	private:
		std::vector<std::shared_ptr<EventHandler>> handlers;
		const Class* eventClass;

	public:
		EventBus(EventBus&) = delete;
		EventBus(EventBus&&) = delete;
		EventBus(const Class* eventClass);

		void addHandler(std::shared_ptr<EventHandler>&);
		void removeHandler(std::shared_ptr<EventHandler>&);
		bool hasHandler(std::shared_ptr<EventHandler>&) const;

		// fireEvent? What did they do?
		void fireEvent(std::shared_ptr<AEvent>) const;
	};

	template<IsEvent E>
	class EventBusLegacy {
		std::vector<std::weak_ptr<IEventListener<E>>> eventListeners;
	public:
		EventBusLegacy() {
			std::println("[WARN] EventBusLegacy is deprecated");
		}

		void operator() (E& event) {
			std::for_each(eventListeners.begin(), eventListeners.end(), [&](auto& listener) {
				if (auto pListener = listener.lock())
					pListener->onEvent(event);
			});
		}

		void operator+= (std::weak_ptr<IEventListener<E>> listener) {
			eventListeners.push_back(listener);
		}

		void operator-= (std::weak_ptr<IEventListener<E>> listener) {
			eventListeners.resize(std::distance(
				eventListeners.begin(),
				std::remove_if(eventListeners.begin(), eventListeners.end(), [&listener](const auto& iter) {
					if(iter.expired()) return true;
					return listener.lock() == iter.lock();
				})
			));
		}
	};	
}
