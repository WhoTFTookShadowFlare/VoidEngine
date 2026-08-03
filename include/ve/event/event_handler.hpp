#pragma once

#include "ve/class_db.hpp"
#include "ve/event/event.hpp"
#include "ve/object.hpp"
#include <memory>
#include <string>

namespace VoidEngine::Event {
	struct EventHandler {
	private:
		std::weak_ptr<Object> handlerObj;
		const MethodBase* func;
	public:
		EventHandler(std::shared_ptr<Object>, const MethodBase*);
		std::shared_ptr<Object> getHandlerObject() const;
		std::string getHandlerMethodName() const;
		void handle(std::shared_ptr<AEvent>& evt) const;

		bool isValid() const;

		bool operator==(const EventHandler&) const;
	};
}
