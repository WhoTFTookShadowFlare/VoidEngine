#pragma once

#include <memory>
#include <vector>
#include "ve/class_db.hpp"
#include "ve/event/event.hpp"
#include "ve/event/event_handler.hpp"

namespace VoidEngine::Event {
	class EventBus final {
	private:
		std::vector<std::shared_ptr<EventHandler>> handlers;
		const Class* eventClass;

	public:
		EventBus(EventBus&) = delete;
		EventBus(EventBus&&) = delete;
		EventBus(const Class* eventClass);

		void addHandler(std::shared_ptr<EventHandler>);
		void removeHandler(std::shared_ptr<EventHandler>);
		bool hasHandler(std::shared_ptr<EventHandler>) const;

		// fireEvent? What did they do?
		void fireEvent(std::shared_ptr<AEvent>) const;
	};
}
