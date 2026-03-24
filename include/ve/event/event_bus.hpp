#pragma once

#include <algorithm>
#include <memory>
#include <vector>
#include "ve/event/event_listener.hpp"

namespace VoidEngine::Event {
	template<typename E>
	class EventBus {
		std::vector<std::weak_ptr<IEventListener<E>>> eventListeners;
	public:
		void operator() (E& event) {
			for(const auto& listener : eventListeners) {
				if(auto pListener = listener.lock())
					pListener->onEvent(event);
			}
		}

		void addListener(std::weak_ptr<IEventListener<E>> listener) {
			eventListeners.push_back(listener);
		}

		void removeListener(std::weak_ptr<IEventListener<E>> listener) {
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
