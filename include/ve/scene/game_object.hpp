#pragma once

#include "ve/scene/object_component.hpp"
#include <memory>
#include <vector>

#include "ve/event/event_bus.hpp"
#include "ve/scene/events.hpp"

namespace VoidEngine::Scene {
	using namespace std;
	class GameObject final : public enable_shared_from_this<GameObject> {
		vector<shared_ptr<AObjectComponent>> components = {};
	public:
		
		void addComponent(shared_ptr<AObjectComponent> component);
		vector<shared_ptr<AObjectComponent>> getComponents();
		void removeComponent(shared_ptr<AObjectComponent> component);

		Event::EventBus<Events::EAddedToScene> onAddedToScene;
		Event::EventBus<Events::ERemovedFromScene> onRemovedFromScene;

		Event::EventBus<Events::EAddedToObject> onComponentAdded;
		Event::EventBus<Events::ERemovedFromObject> onComponentRemoved;

		void draw(double delta);
	};
}
