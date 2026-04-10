#pragma once

#include <memory>
#include <vector>

#include "ve/event/event_bus.hpp"
#include "ve/scene/events.hpp"

namespace VoidEngine::Scene {
	class GameObject;

	class AObjectComponent {
		friend class GameObject;
	private:
		std::vector<std::weak_ptr<GameObject>> tiedTo;

		void cleanTiedTo();

	public:
		virtual ~AObjectComponent() {}

		Event::EventBus<Events::EAddedToObject> onComponentAdded;
		Event::EventBus<Events::ERemovedFromObject> onComponentRemoved;

		Event::EventBus<Events::EComponentUpdate> onUpdate;
		Event::EventBus<Events::EComponentDraw> onDraw;

		std::vector<std::shared_ptr<GameObject>> getObjectsUsing();
	};
}
