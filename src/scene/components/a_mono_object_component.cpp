#include <ve/scene/components/a_mono_object_component.hpp>

#include <ve/scene/game_object.hpp>
#include <ve/class_property.hpp>
#include <ve/class_constructor.hpp>

namespace VoidEngine::Scene::Components {
	const ::VoidEngine::Class AMonoObjectComponent::ClassData = {
		.name = "AMonoObjectComponent",
		.super = &AObjectComponent::ClassData,
		.properties = {
			new NativeProperty("object", &AMonoObjectComponent::scr_getObject)
		},
		.constructor = new NativeConstructor(&AMonoObjectComponent::create)
	};

	Variant AMonoObjectComponent::scr_getObject(void) const {
		return Variant(getObject());
	}

	std::shared_ptr<AMonoObjectComponent> AMonoObjectComponent::create() {
		return std::shared_ptr<AMonoObjectComponent>(new AMonoObjectComponent);
	}

	std::shared_ptr<GameObject> AMonoObjectComponent::getObject() const {
		return object.lock();
	}
}
