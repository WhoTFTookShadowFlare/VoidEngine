#pragma once

#include <ve/scene/components/a_mono_object_component.hpp>
#include <ve/event/event.hpp>

namespace VoidEngine::Scene::Components::GFX {
	class ECameraValueChanged final : public Event::AEvent {
		VE_CLASS(ECameraValueChanged);
	private:

	public:
		static std::shared_ptr<ECameraValueChanged> create();

		bool isSetup() const override;
	};

	class ACameraComponent : public AMonoObjectComponent, public std::enable_shared_from_this<ACameraComponent> {
		VE_CLASS(ACameraComponent);
	private:
	
		Variant scr_makeCurrent(std::vector<Variant>);
		Variant scr_isCurrent(std::vector<Variant>);

		float depth = 100.0f;
	public:
		Event::EventBus onCameraValueChanged = &ECameraValueChanged::ClassData;

		void makeCurrent() const;
		bool isCurrent() const;

		float getDepth() const;
		void setDepth(float);

		virtual glm::mat4 getView() const;
		virtual glm::mat4 getProjection(glm::vec2 resolution) const;
	};
}
