#pragma once

#include <memory>
#include <vector>

#include "ve/event/event_bus.hpp"
#include "ve/scene/events.hpp"

namespace VoidEngine::Scene {
	struct ComponentClass;
	class GameObject;

	template<typename T>
	concept IsAbstractObjectComponent =
		std::is_base_of<AObjectComponent, T>::value &&
		requires(T a) {
			{ T::ClassData } -> std::convertible_to<ComponentClass>;
		};

	template<typename T>
	concept IsObjectComponent =
		IsAbstractObjectComponent<T> &&
		requires(T a) {
			{ T::create() } -> std::convertible_to<std::shared_ptr<AObjectComponent>>;
		};

	class AObjectComponent {
		friend class GameObject;
	private:
		std::vector<std::weak_ptr<GameObject>> tiedTo;

		void cleanTiedTo();

	public:
		static const ComponentClass ClassData;
		virtual ~AObjectComponent() {}

		Event::EventBus<Events::EAddedToObject> onComponentAdded;
		Event::EventBus<Events::ERemovedFromObject> onComponentRemoved;

		Event::EventBus<Events::EComponentUpdate> onUpdate;
		Event::EventBus<Events::EComponentDraw> onDraw;

		std::vector<std::shared_ptr<GameObject>> getObjectsUsing();

		virtual const ComponentClass* getClass() const { return &ClassData; }
	};
}
