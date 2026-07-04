#pragma once

#include <concepts>
#include <memory>
#include <vector>

#include "ve/event/event_bus.hpp"
#include "ve/scene/events.hpp"

namespace VoidEngine::Scene {
	struct Class;
	class GameObject;

	template<typename T>
	concept IsAbstractObjectComponent =
		std::is_base_of<AObjectComponent, T>::value &&
		requires(T a) {
			{ T::ClassData } -> std::convertible_to<Class>;
		};

	template<typename T>
	concept IsObjectComponent =
		IsAbstractObjectComponent<T> &&
		requires(T a) {
			{ T::create() } -> std::convertible_to<std::shared_ptr<AObjectComponent>>;
			// { T::deserialize() } -> std::convertible_to<std::shared_ptr<AObjectComponent>>;
		};

	class AObjectComponent {
		friend class GameObject;
	private:
		std::vector<std::weak_ptr<GameObject>> tiedTo;

		void cleanTiedTo();

	public:
		static const Class ClassData;
		virtual ~AObjectComponent() {}

		Event::EventBus<Events::EComponentAddedToObject> onComponentAdded;
		Event::EventBus<Events::EComponentRemovedFromObject> onComponentRemoved;

		Event::EventBus<Events::EComponentUpdate> onUpdate;
		Event::EventBus<Events::EComponentDraw> onDraw;

		std::vector<std::shared_ptr<GameObject>> getObjectsUsing();

		virtual const Class* getClass() const { return &ClassData; }
	};
}
