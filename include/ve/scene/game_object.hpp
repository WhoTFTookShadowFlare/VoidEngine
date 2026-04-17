#pragma once

#include "ve/scene/object_component.hpp"
#include <memory>
#include <vector>
#include <ranges>

#include "ve/event/event_bus.hpp"
#include "ve/scene/events.hpp"

namespace VoidEngine::Scene {
	using namespace std;

	template<typename T>
	concept IsObjectComponent = std::is_base_of<AObjectComponent, T>::value;

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

		void draw(Events::EComponentDraw& draw);

		template<IsObjectComponent T>
		std::shared_ptr<T> getComponent() {
			auto comp = find_if(components.begin(), components.end(), [](shared_ptr<AObjectComponent> comp) {
				return dynamic_pointer_cast<T>(comp) != nullptr;
			});
			return comp;
		}
	};
}
