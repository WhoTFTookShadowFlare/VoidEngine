#include "ve/event/event_handler.hpp"
#include "ve/class_db.hpp"
#include "ve/variant.hpp"

namespace VoidEngine::Event {
	EventHandler::EventHandler(std::shared_ptr<Object> obj, const EventHandlerBase* func) {
		handlerObj = obj;
		this->func = func;
	}

	std::shared_ptr<Object> EventHandler::getHandlerObject() const {
		if(handlerObj.expired()) return nullptr;
		return handlerObj.lock();
	}
	
	const EventHandlerBase* EventHandler::getHandlerFunction() const {
		return func;
	}
	
	void EventHandler::handle(std::shared_ptr<AEvent>& evt) const {
		if(!isValid()) return;
		func->handleEvent(getHandlerObject(), evt);
	}

	bool EventHandler::isValid() const {
		return !handlerObj.expired() && func != nullptr;
	}

	bool EventHandler::operator==(const EventHandler& RHS) const {
		return handlerObj.lock() == RHS.handlerObj.lock() && func == RHS.func;
	}
}
