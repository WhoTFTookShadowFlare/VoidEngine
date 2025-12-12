#pragma once

#include <algorithm>
#include <memory>
#include <vector>
#include "event/event_listener.hpp"

namespace VoidEngine::Event {
	template<typename E>
	class EventBus {
		std::vector<std::shared_ptr<IEventListener<E>>> eventListeners;
	public:
		void postEvent(E& event) {
			for(const auto& listener : eventListeners) {
				listener->onEvent(event);
			}
		}

		void addListener(std::shared_ptr<IEventListener<E>> listener) {
			eventListeners.push_back(listener);
		}

		void removeListener(std::shared_ptr<IEventListener<E>> listener) {
			eventListeners.erase(std::find(eventListeners.begin(), eventListeners.end(), listener));
		}
	};	
}
