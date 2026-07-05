#pragma once

#include <glm/ext/matrix_float4x4.hpp>
#include "ve/scene/object_component.hpp"
#include "ve/class_db.hpp"
#include "ve/variant.hpp"

namespace VoidEngine::IO {
	class Window;
}

namespace VoidEngine::Scene::Components {
	class TransformComponent;

	class ACamera : public AObjectComponent {
	private:
		float zFar = 200.0f;
	public:
		static const Class ClassData;
		virtual const Class* getClass() const override { return &ClassData; }
		
		virtual glm::mat4 getView(std::shared_ptr<GameObject> obj);

		virtual glm::mat4 getProjection(std::shared_ptr<IO::Window> window) = 0;

		Variant getZFar() const;
		void setZFar(Variant);
	};

	class PerspectiveCamera : public ACamera {
	private:
		float fov = 90.0f;
	public:
		static const Class ClassData;
		virtual const Class* getClass() const override { return &ClassData; }

		static std::shared_ptr<PerspectiveCamera> create();

		glm::mat4 getProjection(std::shared_ptr<IO::Window> window) override;

		Variant getFOV() const;
		void setFOV(Variant);
	};

	class OrthoCamera : public ACamera {
	public:
		static const Class ClassData;
		static std::shared_ptr<OrthoCamera> create();

		glm::mat4 getProjection(std::shared_ptr<IO::Window> window) override;

		virtual const Class* getClass() const override { return &ClassData; }
	};
}
