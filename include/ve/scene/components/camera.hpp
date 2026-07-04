#pragma once

#include <glm/ext/matrix_float4x4.hpp>
#include "ve/scene/object_component.hpp"
#include "ve/class_db.hpp"

namespace VoidEngine::IO {
	class Window;
}

namespace VoidEngine::Scene::Components {
	class TransformComponent;

	class ACamera : public AObjectComponent {
	private:
	public:
		static const Class ClassData;
		
		virtual glm::mat4 getView(std::shared_ptr<GameObject> obj);

		virtual glm::mat4 getProjection(std::shared_ptr<IO::Window> window) = 0;

		virtual const Class* getClass() const override { return &ClassData; }
	};

	class PerspectiveCamera : public ACamera {
	public:
		static const Class ClassData;
		static std::shared_ptr<PerspectiveCamera> create();

		float fov = 90.0f;

		glm::mat4 getProjection(std::shared_ptr<IO::Window> window) override;

		virtual const Class* getClass() const override { return &ClassData; }
	};

	class OrthoCamera : public ACamera {
	public:
		static const Class ClassData;
		static std::shared_ptr<OrthoCamera> create();

		glm::mat4 getProjection(std::shared_ptr<IO::Window> window) override;

		virtual const Class* getClass() const override { return &ClassData; }
	};
}
