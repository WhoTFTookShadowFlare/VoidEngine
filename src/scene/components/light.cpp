#include "ve/scene/components/light.hpp"
#include "ve/io/gfx/light.hpp"
#include "ve/scene/game_object.hpp"
#include <algorithm>
#include <memory>

namespace VoidEngine::Scene::Components {
	const Class LightComponent::ClassData = {
		.name = "LightComponent"
	};

	LightComponent::LightComponent() {}

	std::shared_ptr<LightComponent> LightComponent::create() {
		std::shared_ptr<LightComponent> self(new LightComponent);
		self->onDraw += self;
		return self;
	}

	void LightComponent::onEvent(Events::EComponentDraw& evt) {
		auto objs = getObjectsUsing();
		std::for_each(objs.cbegin(), objs.cend(), [&](const auto& obj) {
			IO::GFX::Light light;
			light.position = obj->getPosition().asVec3().value();
			light.ambient = ambient;
			light.diffuse = diffuse;
			light.specular = specular;
			evt.frame->addLight(light);
		});
	}
		
	glm::vec3 LightComponent::getAmbient() {
		return ambient;
	}

	void LightComponent::setAmbient(glm::vec3 value) {
		ambient = value;
	}

	glm::vec3 LightComponent::getDiffuse() {
		return diffuse;
	}

	void LightComponent::setDiffuse(glm::vec3 value) {
		diffuse = value;
	}

	glm::vec3 LightComponent::getSpecular() {
		return specular;
	}

	void LightComponent::setSpecular(glm::vec3 value) {
		specular = value;
	}
}