#include <ve/scene/components/a_object_component.hpp>

#include <ve/class_event_bus.hpp>

namespace VoidEngine::Scene::Components {
	const ::VoidEngine::Class AObjectComponent::ClassData = {
		.name = "AObjectComponent",
		.super = &Object::ClassData,
		.eventBusses = {
			new NativeEventBus(&ESceneUpdate::ClassData, &AObjectComponent::onSceneUpdate)
		}
	};
}
