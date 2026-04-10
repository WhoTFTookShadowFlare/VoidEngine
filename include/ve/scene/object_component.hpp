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
		virtual void update(double delta) = 0;
		virtual void draw(double delta) = 0;

		Event::EventBus<Events::EAddedToObject> onComponentAdded;
		Event::EventBus<Events::ERemovedFromObject> onComponentRemoved;

		std::vector<std::shared_ptr<GameObject>> getObjectsUsing();
	};
}
