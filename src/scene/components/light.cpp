#include "ve/scene/components/light.hpp"
#include "ve/class_db.hpp"
#include "ve/io/gfx/light.hpp"
#include "ve/scene/game_object.hpp"
#include <algorithm>
#include <memory>

namespace VoidEngine::Scene::Components {
	const Class LightComponent::ClassData = {
		.name = "LightComponent"
	};

	const Class PointLightComponent::ClassData = {
		.name = "PointLightComponent"
	};

	LightComponent::LightComponent() {}

	void PointLightComponent::onEvent(Events::EComponentDraw& evt) {
		auto objs = getObjectsUsing();
		std::for_each(objs.cbegin(), objs.cend(), [&](const std::shared_ptr<GameObject>& obj) {
			IO::GFX::PointLight light;
			light.position = obj->getPosition().asVec3().value();
			light.diffuse = getDiffuse();
			light.specular = getSpecular();

			light.constant = constant;
			light.linear = linear;
			light.quadratic = quadratic;

			evt.frame->addLight(light);
		});
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

	std::shared_ptr<PointLightComponent> PointLightComponent::create() {
		std::shared_ptr<PointLightComponent> self(new PointLightComponent);
		self->onDraw += self;
		return self;
	}
}