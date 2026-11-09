#include <ve/scene/components/a_object_component.hpp>

#include <ve/class_event_bus.hpp>

namespace VoidEngine::Scene::Components {
	const ::VoidEngine::Class AObjectComponent::ClassData = {
		.name = "AObjectComponent",
		.super = &Object::ClassData,
		.eventBusses = {
			new NativeEventBus(&EAddedToScene::ClassData, &AObjectComponent::onAddedToScene),
			new NativeEventBus(&ERemovedFromScene::ClassData, &AObjectComponent::onRemovedFromScene),
			new NativeEventBus(&EComponentAdded::ClassData, &AObjectComponent::onAddedToObject),
			new NativeEventBus(&EComponentRemoved::ClassData, &AObjectComponent::onRemovedFromObject),
			new NativeEventBus(&ESceneUpdate::ClassData, &AObjectComponent::onSceneUpdate),
			new NativeEventBus(&ESceneDraw::ClassData, &AObjectComponent::onSceneDraw)
		}
	};
}
