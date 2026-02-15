#include "ve/scene/components/transform.hpp"
#include "ve/cs/scene/module.hpp"
#include <glm/ext/matrix_float4x4.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/trigonometric.hpp>
#include <mono-2.0/mono/metadata/object-forward.h>

namespace VoidEngine::Scene::Components {
	MonoClass *TransformComponent::getCSClass() {
		return VoidEngine::CS::Scene::getTransformComponentClass();
	}
	glm::mat4 TransformComponent::getMatrix() {
		glm::mat4 matrix(1.0f);
		
		if(auto parent = this->parentTransform.lock()) {
			matrix = parent->getMatrix();
		}

		matrix = glm::rotate(matrix, glm::radians(rotation.x), { 1.0f, 0.0f, 0.0f });
		matrix = glm::rotate(matrix, glm::radians(rotation.y), { 0.0f, 1.0f, 0.0f });
		matrix = glm::rotate(matrix, glm::radians(rotation.z), { 0.0f, 0.0f, 1.0f });

		matrix = glm::scale(matrix, scale);
		matrix = glm::translate(matrix, position);
		
		return matrix;
	}
}

