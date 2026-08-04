#pragma once

#include <memory>
#include <vector>
#include "ve/class_db.hpp"
#include "ve/event/event.hpp"
#include "ve/event/event_handler.hpp"

namespace VoidEngine::Event {
	class EventBus final {
	private:
		std::vector<EventHandler> handlers;
		const Class* eventClass;

	public:
		EventBus(EventBus&) = delete;
		EventBus(EventBus&&) = delete;
		EventBus(const Class* eventClass);

		// TODO: addHandler takes the OBJECT and generates the EventHandler from that
		void addHandler(std::shared_ptr<Object>);
		void removeHandler(std::shared_ptr<Object>);
		bool hasHandler(std::shared_ptr<Object>) const;

		// fireEvent? What did they do?
		void fireEvent(std::shared_ptr<AEvent>) const;
	};
}
