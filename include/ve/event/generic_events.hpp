#pragma once

namespace VoidEngine::Events {
	template <typename T>
	class GenericEvent {
		T value;
	public:
		GenericEvent(T value) : value(value) {}
		T getValue() { return value; }
	};
}
