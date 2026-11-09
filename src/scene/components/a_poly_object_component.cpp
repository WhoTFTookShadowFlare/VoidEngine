#include <ve/scene/components/a_poly_object_component.hpp>

#include <ve/class_property.hpp>
#include <ve/class_methods.hpp>

#include <ve/scene/scene.hpp>
#include <ve/scene/game_object.hpp>

namespace VoidEngine::Scene::Components {
	const ::VoidEngine::Class APolyObjectComponent::ClassData = {
		.name = "APolyObjectComponent",
		.super = &AObjectComponent::ClassData,
		.properties = {
			new NativeProperty("objects", &APolyObjectComponent::scr_getObjects)
		},
		.methods = {
			new NativeMethod("isBoundToScene", &APolyObjectComponent::scr_isBoundToScene),
			new NativeMethod("isBoundToAny", &APolyObjectComponent::scr_isBoundToAnyScene),
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

	Variant APolyObjectComponent::scr_isBoundToScene(std::vector<Variant> args) {
		if(args.size() != 1) {
			std::println("[ERR] APolyObjectComponent.isBoundToScene takes 1 arg (Scene)");
			return false;
		}

		auto arg0 = args[0];
		if(!arg0.isObject()) {
			std::println("[ERR] APolyObjectComponent.isBoundToScene takes 1 arg (Scene)");
			return false;
		}

		auto obj = arg0.asObject().value();
		if(!obj->getClass()->instanceOf(&Scene::ClassData)) {
			std::println("[ERR] APolyObjectComponent.isBoundToScene takes 1 arg (Scene)");
			return false;
		}

		return isBoundToScene(std::static_pointer_cast<Scene>(obj));
	}
	
	Variant APolyObjectComponent::scr_isBoundToAnyScene(std::vector<Variant>) {
		return isBoundToAnyScene();
	}
	
	std::vector<std::shared_ptr<GameObject>> APolyObjectComponent::getObjects() const {
		std::vector<std::shared_ptr<GameObject>> objectLocks;

		for(const std::weak_ptr<GameObject>& objRef : objects) {
			if(!objRef.expired()) objectLocks.push_back(objRef.lock());
		}

		return objectLocks;
	}

	bool APolyObjectComponent::isBoundToScene(std::shared_ptr<Scene> scene) const {
		return this->scene.lock() == scene;
	}

	bool APolyObjectComponent::isBoundToAnyScene() const {
		return !isBoundToScene(nullptr);
	}
}
