#include "ve/scene/components/light.hpp"
#include <glm/ext/vector_float3.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include "ve/class_db.hpp"
#include "ve/class_event_handler.hpp"
#include "ve/io/gfx/light.hpp"
#include "ve/scene/events.hpp"
#include "ve/scene/game_object.hpp"
#include <algorithm>
#include <memory>

namespace VoidEngine::Scene::Components {
	const Class LightComponent::ClassData = {
		.name = "LightComponent"
	};

	const Class PointLightComponent::ClassData = {
		.name = "PointLightComponent",
		.eventHandlers = {
			new NativeEventHandler(&Events::EComponentDraw::ClassData, &PointLightComponent::onDrawEvent)
		},
		.constructor = new NativeConstructor(PointLightComponent::create),
	};

	const Class SpotLightComponent::ClassData = {
		.name = "SpotLightComponent",
		.eventHandlers = {
			new NativeEventHandler(&Events::EComponentDraw::ClassData, &SpotLightComponent::onDrawEvent)
		},
		.constructor = new NativeConstructor(SpotLightComponent::create),
	};

	LightComponent::LightComponent() {}

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
		self->onDraw.addHandler(self);
		return self;
	}

	void PointLightComponent::onDrawEvent(std::shared_ptr<Object> draw) {
		auto evt = std::static_pointer_cast<Events::EComponentDraw>(draw);

		auto objs = getObjectsUsing();
		std::for_each(objs.cbegin(), objs.cend(), [&](const std::shared_ptr<GameObject>& obj) {
			IO::GFX::PointLight light;
			light.position = obj->getPosition().asVec3().value();
			light.diffuse = getDiffuse();
			light.specular = getSpecular();

			light.constant = constant;
			light.linear = linear;
			light.quadratic = quadratic;

			evt->frame->addPointLight(light);
		});
	}

	std::shared_ptr<SpotLightComponent> SpotLightComponent::create() {
		std::shared_ptr<SpotLightComponent> self(new SpotLightComponent);
		self->onDraw.addHandler(self);
		return self;
	}

	void SpotLightComponent::onDrawEvent(std::shared_ptr<Object> draw) {
		auto evt = std::static_pointer_cast<Events::EComponentDraw>(draw);

		auto objs = getObjectsUsing();
		std::for_each(objs.cbegin(), objs.cend(), [&](const std::shared_ptr<GameObject>& obj) {
			IO::GFX::SpotLight light;
			light.position = obj->getPosition().asVec3().value();
			light.diffuse = getDiffuse();
			light.specular = getSpecular();

			auto rotation = obj->getRotation().asVec3().value();
			light.direction = glm::vec3(0.0f, 0.0f, -1.0f);
			light.direction = glm::rotateX(light.direction, rotation.x);
			light.direction = glm::rotateY(light.direction, rotation.y);
			light.direction = glm::rotateZ(light.direction, rotation.z);

			light.constant = constant;
			light.linear = linear;
			light.quadratic = quadratic;
			light.cutoffAngle = cutoffAngle;
			light.outerCutoffAngle = outerCutoffAngle;

			evt->frame->addSpotLight(light);
		});
	}
}