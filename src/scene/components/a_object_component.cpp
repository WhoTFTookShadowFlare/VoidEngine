#include <ve/scene/components/a_object_component.hpp>

namespace VoidEngine::Scene::Components {
	const ::VoidEngine::Class AObjectComponent::ClassData = {
		.name = "AObjectComponent",
		.super = &Object::ClassData
	};
}
