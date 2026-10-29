#pragma once

#include <ve/scene/components/gfx/a_camera_component.hpp>

#include <glm/ext/vector_float2.hpp>

namespace VoidEngine::Scene::Components::GFX {
	class OrthoCameraComponent final : public ACameraComponent {
		VE_CLASS(OrthoCameraComponent);
	private:
		OrthoCameraComponent() = default;

		glm::vec2 resolution = { 800, 600 };
		bool centered = true;

		void scr_setCentered(Variant);
		Variant scr_isCentered(void) const;

	public:
		static std::shared_ptr<OrthoCameraComponent> create();

		bool isCentered() const;
		void setCentered(bool);

		glm::mat4 getProjection(glm::vec2 resolution) const override;
	};
}
