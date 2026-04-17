#pragma once

#include <glm/ext/matrix_float4x4.hpp>
#include "ve/scene/object_component.hpp"

namespace VoidEngine::IO {
	class Window;
}

namespace VoidEngine::Scene::Components {
	class TransformComponent;

	class ACamera : public AObjectComponent {
	private:
		std::shared_ptr<TransformComponent> transform;
	public:
		virtual glm::mat4 getView();

		virtual glm::mat4 getProjection(std::shared_ptr<IO::Window> window) = 0;
	};

	class PerspectiveCamera : public ACamera {
	public:
		float fov = 90.0f;

		glm::mat4 getProjection(std::shared_ptr<IO::Window> window);
	};

	class OrthoCamera : public ACamera {
	public:
		glm::mat4 getProjection(std::shared_ptr<IO::Window> window);
	};
}
