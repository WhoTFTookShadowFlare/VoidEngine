#include "ve/event/event_bus.hpp"

namespace VoidEngine::Event {
	// void EventBus::operator() (std::shared_ptr<AEvent>& event) {
	// 	std::for_each(eventListeners.begin(), eventListeners.end(), [&](auto& listener) {
	// 		if (auto pListener = listener.lock())
	// 			pListener->onEvent(event);
	// 	});
	// }

	// void EventBus::operator+= (std::weak_ptr<Object> listener) {
	// 	eventListeners.push_back(listener);
	// }

	// void EventBus::operator-= (std::weak_ptr<Object> listener) {
	// 	eventListeners.resize(std::distance(
	// 		eventListeners.begin(),
	// 		std::remove_if(eventListeners.begin(), eventListeners.end(), [&listener](const auto& iter) {
	// 			if(iter.expired()) return true;
	// 			return listener.lock() == iter.lock();
	// 		})
	// 	));
	// }
}
