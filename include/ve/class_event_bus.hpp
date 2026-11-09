#pragma once

#include <ve/class_db.hpp>

namespace VoidEngine {
	template<IsAbstractClass T>
	struct NativeEventBus final : public EventBusBase {
	private:
		const Event::EventBus T::* bus;
	public:
		NativeEventBus(const Class* event, const Event::EventBus T::* bus) : EventBusBase(event), bus(bus)
		{}

		~NativeEventBus() = default;

		virtual Event::EventBus* getEventBus(std::shared_ptr<Object> obj) const {
			if(obj == nullptr) {
				return nullptr;
			}
			if(!obj->getClass()->instanceOf(&T::ClassData)) {
				std::println("[ERR] No event bus for {} on object of class {}", getEventClass()->getName(), obj->getClass()->getName());
				return nullptr;
			}

			return const_cast<Event::EventBus*>(&(std::static_pointer_cast<T>(obj).get()->*bus));
		}

		virtual void fireEvent(std::shared_ptr<Object> obj, std::shared_ptr<Event::AEvent> event) const {
			Event::EventBus* bus = getEventBus(obj);
			if(bus == nullptr) {
				return;
			}

			bus->fireEvent(event);
		}
	};
}
