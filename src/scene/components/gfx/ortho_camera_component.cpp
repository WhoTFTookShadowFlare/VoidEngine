#include <ve/scene/components/gfx/ortho_camera_component.hpp>

#include <ve/class_property.hpp>
#include <ve/struct_db.hpp>

#include <glm/gtc/matrix_transform.hpp>

namespace VoidEngine::Scene::Components::GFX {
	const ::VoidEngine::Class ECameraValueChanged::ClassData = {
		.name = "ECameraValueChanged",
		.super = &Event::AEvent::ClassData,
		.flags = ClassFlags::FINAL
	};

	std::shared_ptr<ECameraValueChanged> ECameraValueChanged::create() {
		return std::shared_ptr<ECameraValueChanged>(new ECameraValueChanged);
	}

	bool ECameraValueChanged::isSetup() const {
		return true;
	}

	const ::VoidEngine::Class OrthoCameraComponent::ClassData = {
		.name = "OrthoCameraComponent",
		.super = &ACameraComponent::ClassData,
		.properties = {
			new NativeProperty("centered", &OrthoCameraComponent::scr_isCentered, &OrthoCameraComponent::scr_setCentered)
		},
		.constructor = new NativeConstructor(&OrthoCameraComponent::create),
		.flags = ClassFlags::FINAL
	};

	std::shared_ptr<OrthoCameraComponent> OrthoCameraComponent::create() {
		return std::shared_ptr<OrthoCameraComponent>(new OrthoCameraComponent);
	}
	
	Variant OrthoCameraComponent::scr_isCentered(void) const {
		return isCentered();
	}
	
	void OrthoCameraComponent::scr_setCentered(Variant value) {
		if(!value.isBool()) {
			std::println("[ERR] OrthoCameraComponent.centered must be a bool");
			return;
		}

		setCentered(value.asBool().value());
	}
	
	bool OrthoCameraComponent::isCentered() const {
		return centered;
	}
	
	void OrthoCameraComponent::setCentered(bool value) {
		centered = value;
		auto evt = ECameraValueChanged::create();
		onCameraValueChanged.fireEvent(evt);
	}
	
	glm::mat4 OrthoCameraComponent::getProjection(glm::vec2 resolution) const {
		if(isCentered())
			return glm::ortho(-resolution.x / 2, resolution.x / 2, -resolution.y / 2, resolution.y / 2, 0.01f, getDepth());
		return glm::ortho(0.0f, resolution.x, 0.0f, resolution.y, 0.01f, getDepth());
	}
}
