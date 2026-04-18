#pragma once

#include "ve/scene/object_component.hpp"

#include <typeindex>
#include <memory>
#include <vector>
#include <map>
#include <ranges>

#include "ve/event/event_bus.hpp"
#include "ve/scene/events.hpp"

#include "ve/scene/component_db.hpp"

namespace VoidEngine::Scene {
	using namespace std;

	class GameObject final : public enable_shared_from_this<GameObject> {
		std::map<const ComponentClass*, shared_ptr<AObjectComponent>> components;
	public:
		
		vector<shared_ptr<AObjectComponent>> getComponents();

		void addComponent(shared_ptr<AObjectComponent> component);
		void removeComponent(shared_ptr<AObjectComponent> component);

		Event::EventBus<Events::EAddedToScene> onAddedToScene;
		Event::EventBus<Events::ERemovedFromScene> onRemovedFromScene;

		Event::EventBus<Events::EAddedToObject> onComponentAdded;
		Event::EventBus<Events::ERemovedFromObject> onComponentRemoved;

		void draw(Events::EComponentDraw& draw);

		std::shared_ptr<AObjectComponent> getComponent(const ComponentClass* cls);
		std::shared_ptr<AObjectComponent> getFirstComponentOfInstance(const ComponentClass* cls);
	};
}
