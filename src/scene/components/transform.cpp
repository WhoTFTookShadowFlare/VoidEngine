#include "ve/scene/components/transform.hpp"
#include <glm/ext/matrix_float4x4.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/trigonometric.hpp>

namespace VoidEngine::Scene::Components {
	glm::mat4 TransformComponent::getMatrix() {
		glm::mat4 matrix(1.0f);
		
		if(auto parent = this->parentTransform.lock()) {
			matrix = parent->getMatrix();
		}

		matrix = glm::translate(matrix, position);
		matrix = glm::rotate(matrix, glm::radians(rotation.x), { 1.0f, 0.0f, 0.0f });
		matrix = glm::rotate(matrix, glm::radians(rotation.y), { 0.0f, 1.0f, 0.0f });
		matrix = glm::rotate(matrix, glm::radians(rotation.z), { 0.0f, 0.0f, 1.0f });
		matrix = glm::scale(matrix, scale);
		
		return matrix;
	}
}

