#include <ve/scene/components/gfx/a_camera_component.hpp>

#include <ve/class_methods.hpp>
#include <ve/scene/game_object.hpp>
#include <ve/scene/scene.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace VoidEngine::Scene::Components::GFX {
	const ::VoidEngine::Class ACameraComponent::ClassData = {
		.name = "ACameraComponent",
		.super = &AMonoObjectComponent::ClassData,
		.methods = {

		}
	};

	Variant ACameraComponent::scr_isCurrent(std::vector<Variant>) {
		return isCurrent();
	}

	Variant ACameraComponent::scr_makeCurrent(std::vector<Variant>) {
		makeCurrent();
		return nullptr;
	}

	bool ACameraComponent::isCurrent() const {
		auto obj = getObject();
		if(obj == nullptr) return false;
		std::shared_ptr<Scene> scn = obj->getScene();
		if(scn == nullptr) return false;

		return scn->getCurrentCamera().get() == this;
	}

	void ACameraComponent::makeCurrent() const {
		auto obj = getObject();
		if (obj == nullptr) return;
		std::shared_ptr<Scene> scn = obj->getScene();
		if (scn == nullptr) return;
		scn->setCurrentCamera(std::const_pointer_cast<ACameraComponent>(shared_from_this()));
	}

	float ACameraComponent::getDepth() const {
		return depth;
	}

	void ACameraComponent::setDepth(float value) {
		depth = value;
		onCameraValueChanged.fireEvent(ECameraValueChanged::create());
	}

	glm::mat4 ACameraComponent::getView() const {
		auto obj = getObject();
		if(obj == nullptr) return glm::mat4(1.0);
		return glm::lookAt(obj->position, obj->position + glm::vec3 { 0, 0, -1 }, { 0, 1, 0 });
	}
	
	glm::mat4 ACameraComponent::getProjection(glm::vec2 resolution) const {
		assert(false);
		return glm::mat4(1.0);
	}
}
