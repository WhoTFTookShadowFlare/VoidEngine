#pragma once

#include "class_db.hpp"
#include "ve/object.hpp"
#include <functional>
#include <memory>

namespace VoidEngine {
	template<IsAbstractClass T>
	struct NativeEventHandler final : public EventHandlerBase {
		using EventFunc = void (T::*) (std::shared_ptr<Object>);
	private:
		const EventFunc fn;
	public:
		NativeEventHandler(const Class* event, EventFunc fn) : EventHandlerBase(event), fn(fn) {}

		virtual void handleEvent(std::shared_ptr<Object> obj, std::shared_ptr<Object> event) const {
			if(obj == nullptr) return;
			if(!obj->getClass()->instanceOf(&T::ClassData)) return;
			(std::static_pointer_cast<T>(obj).get()->*fn)(event);
		};
	};
}
