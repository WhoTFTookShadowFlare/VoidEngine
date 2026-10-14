#include <ve/scene/components/a_poly_object_component.hpp>

#include <ve/class_property.hpp>

#include <ve/scene/game_object.hpp>

namespace VoidEngine::Scene::Components {
	const ::VoidEngine::Class APolyObjectComponent::ClassData = {
		.name = "APolyObjectComponent",
		.super = &AObjectComponent::ClassData,
		.properties = {
			new NativeProperty("objects", &APolyObjectComponent::scr_getObjects)
		}
	};

	Variant APolyObjectComponent::scr_getObjects(void) const {
		std::vector<std::shared_ptr<GameObject>> objects = getObjects();
		std::vector<Variant> conv(objects.size());
		
		for(const std::shared_ptr<GameObject>& obj : objects) {
			conv.emplace_back(obj);
		}

		return conv;
	}
	
	std::vector<std::shared_ptr<GameObject>> APolyObjectComponent::getObjects() const {
		std::vector<std::shared_ptr<GameObject>> objectLocks(objects.size());

		for(const std::weak_ptr<GameObject>& objRef : objects) {
			if(!objRef.expired()) objectLocks.push_back(objRef.lock());
		}

		return objectLocks;
	}
}
