#include <ve/scene/components/a_mono_object_component.hpp>

#include <ve/scene/game_object.hpp>
#include <ve/class_property.hpp>

namespace VoidEngine::Scene::Components {
	const ::VoidEngine::Class AMonoObjectComponent::ClassData = {
		.name = "AMonoObjectComponent",
		.super = &AObjectComponent::ClassData,
		.properties = {
			new NativeProperty("object", &AMonoObjectComponent::scr_getObject)
		}
	};

	Variant AMonoObjectComponent::scr_getObject(void) const {
		return Variant(getObject());
	}

	std::shared_ptr<GameObject> AMonoObjectComponent::getObject() const {
		return object.lock();
	}
}
