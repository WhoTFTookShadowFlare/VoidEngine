#pragma once

#include "ve/event/event.hpp"
#include <print>
#include <type_traits>

namespace VoidEngine::Event {
	template<class T>
	concept IsEvent =
		std::is_base_of<AEvent, T>::value;

	template <IsEvent E>
	class IEventListener {
	public:
		IEventListener() {
			std::println("[WARN] IEventListener<T> is deprecated");
		}
		
		virtual void onEvent(E& event) = 0;
	};
}
