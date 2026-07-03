#include "ve/scene/component_db.hpp"

#include "ve/scene/components/mesh.hpp"
#include "ve/scene/components/sound.hpp"
#include "ve/scene/components/camera.hpp"

namespace VoidEngine::Scene {
	std::shared_ptr<ComponentDB> ComponentDB::instance = nullptr;

	ComponentDB::ComponentDB() {
		registerClass<Components::MeshComponent, AObjectComponent>();

		registerClass<Components::SoundComponent, AObjectComponent>();

		registerAbstractClass<Components::ACamera, AObjectComponent>();
		registerClass<Components::OrthoCamera, Components::ACamera>();
		registerClass<Components::PerspectiveCamera, Components::ACamera>();
	}

	std::shared_ptr<ComponentDB> ComponentDB::getInstance() {
		if(instance == nullptr) instance = std::shared_ptr<ComponentDB>(new ComponentDB);
		return instance;
	}

	const ComponentClass* ComponentDB::getClassByName(std::string name) {
		return componentClasses[name];
	}
}
