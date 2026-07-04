#include "ve/class_db.hpp"

#include "ve/scene/components/mesh.hpp"
#include "ve/scene/components/sound.hpp"
#include "ve/scene/components/camera.hpp"

namespace VoidEngine::Scene {
	std::shared_ptr<ClassDB> ClassDB::instance = nullptr;

	ClassDB::ClassDB() {
		registerClass<Components::MeshComponent, AObjectComponent>();

		registerClass<Components::SoundComponent, AObjectComponent>();

		registerAbstractClass<Components::ACamera, AObjectComponent>();
		registerClass<Components::OrthoCamera, Components::ACamera>();
		registerClass<Components::PerspectiveCamera, Components::ACamera>();
	}

	std::shared_ptr<ClassDB> ClassDB::getInstance() {
		if(instance == nullptr) instance = std::shared_ptr<ClassDB>(new ClassDB);
		return instance;
	}

	const Class* ClassDB::getClassByName(std::string name) {
		return componentClasses[name];
	}
}
