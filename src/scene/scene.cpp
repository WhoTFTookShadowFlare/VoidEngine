#include <ve/scene/scene.hpp>
#include <ve/scene/game_object.hpp>

#include <ve/class_event_handler.hpp>

#include <ve/physics2d/physics_2d.hpp>

namespace VoidEngine::Scene {
	const ::VoidEngine::Class Scene::ClassData = {
		.name = "Scene",
		.super = &Object::ClassData,
		.eventHandlers = {
			new NativeEventHandler(&EObjectRenamed::ClassData, &Scene::handleObjectRenamed)
		},
		.constructor = new NativeConstructor(&Scene::create),
		.flags = ClassFlags::FINAL
	};

	Scene::Scene() {
		world2d = Physics2D::Physics2D::getInstance()->createWorld();
	}

	Scene::~Scene() {}

	std::shared_ptr<Scene> Scene::create() {
		return std::shared_ptr<Scene>(new Scene);
	}

	void Scene::handleObjectRenamed(std::shared_ptr<Object> evtObj) {
		std::shared_ptr<EObjectRenamed> evt = std::static_pointer_cast<EObjectRenamed>(evtObj);
		
		objects[evt->getObject()->getName()] = objects[evt->getOldName()];
		objects.erase(evt->getOldName());
	}

	std::shared_ptr<GameObject> Scene::getObject(std::string name) {
		if(objects.contains(name)) return objects[name];
		return nullptr;
	}

	void Scene::addObject(std::shared_ptr<GameObject> obj) {
		if(getObject(obj->getName()) != nullptr) {
			std::println("[WARN] Object with name {} already in scene, adding suffix", obj->getName());
			obj->setName(std::format("{}{}", obj->getName(), reinterpret_cast<size_t>(obj.get())));
		}

		objects[obj->getName()] = obj;
		obj->onRename.addHandler(shared_from_this());

		auto evt = EAddedToScene::create();
		evt->scene = shared_from_this();
		obj->onAddedToScene.fireEvent(evt);
	}

	void Scene::removeObject(std::string name) {
		auto object = getObject(name);
		if(object == nullptr) return;
		objects.erase(name);

		auto evt = ERemovedFromScene::create();
		evt->object = object;
		object->onRemovedFromScene.fireEvent(evt);
	}
}
