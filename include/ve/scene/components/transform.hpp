#pragma once

#include "ve/scene/object_component.hpp"
#include <glm/ext/matrix_float4x4.hpp>
#include <glm/ext/vector_float3.hpp>
#include <memory>
#include <mono-2.0/mono/metadata/object-forward.h>

namespace VoidEngine::Scene::Components {
	class TransformComponent : public AObjectComponent {
		std::weak_ptr<TransformComponent> parentTransform;

	public:
		glm::vec3
			position = { 0.0f, 0.0f, 0.0f },
			rotation = { 0.0f, 0.0f, 0.0f },
			scale = { 1.0f, 1.0f, 1.0f };

		void update(double delta) override {}
		void draw(double delta) override {}
		MonoClass *getCSClass() override;

		glm::mat4 getMatrix();
	};
}

