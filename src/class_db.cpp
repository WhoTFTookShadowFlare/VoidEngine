#include "ve/class_db.hpp"

#include "ve/object.hpp"
#include "ve/scene/components/mesh.hpp"
#include "ve/scene/components/sound.hpp"
#include "ve/scene/components/camera.hpp"
#include "ve/scene/object_component.hpp"
#include "ve/scene/scene.hpp"

namespace VoidEngine {
	std::shared_ptr<ClassDB> ClassDB::instance = nullptr;

	ClassDB::ClassDB() {
		registerClass<Scene::Scene, Object>();
		// registerClass<Scene::GameObject, Object>();

		registerAbstractClass<Scene::AObjectComponent, Object>();

		registerClass<Scene::Components::MeshComponent, Scene::AObjectComponent>();

		registerClass<Scene::Components::SoundComponent, Scene::AObjectComponent>();

		registerAbstractClass<Scene::Components::ACamera, Scene::AObjectComponent>();
		registerClass<Scene::Components::OrthoCamera, Scene::Components::ACamera>();
		registerClass<Scene::Components::PerspectiveCamera, Scene::Components::ACamera>();
	}

	std::shared_ptr<ClassDB> ClassDB::getInstance() {
		if(instance == nullptr) instance = std::shared_ptr<ClassDB>(new ClassDB);
		return instance;
	}

	const Class* ClassDB::getClassByName(std::string name) {
		return componentClasses[name];
	}
}
