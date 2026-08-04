#pragma once

#include "ve/class_db.hpp"
#include "ve/event/event.hpp"
#include "ve/object.hpp"
#include <memory>

namespace VoidEngine::Event {
	struct EventHandler {
	private:
		std::weak_ptr<Object> handlerObj;
		const EventHandlerBase* func;
	public:
		EventHandler(std::shared_ptr<Object>, const EventHandlerBase*);
		std::shared_ptr<Object> getHandlerObject() const;
		const EventHandlerBase* getHandlerFunction() const;
		void handle(std::shared_ptr<AEvent>& evt) const;

		bool isValid() const;

		bool operator==(const EventHandler&) const;
	};
}
