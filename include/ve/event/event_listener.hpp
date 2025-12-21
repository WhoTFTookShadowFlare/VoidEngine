#pragma once

namespace VoidEngine::Event {
	template <typename E>
	class IEventListener {
	public:
		virtual void onEvent(E& event) = 0;
	};
}
