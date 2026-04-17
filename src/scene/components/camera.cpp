#include "ve/scene/components/camera.hpp"

#include "ve/io/window.hpp"
#include "ve/scene/components/transform.hpp"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/rotate_vector.hpp>

namespace VoidEngine::Scene::Components {
	glm::mat4 ACamera::getView() {
		// TODO: Properly handle transform
		if (transform == nullptr) return glm::mat4(1.0f);

		glm::vec3 position = transform->position;
		glm::vec3 direction = 
			glm::rotateZ(
				glm::rotateY(
					glm::rotateX(
						glm::vec3(0, 0, -1),
						transform->rotation.x
					),
					transform->rotation.y
				),
				transform->rotation.z
			);
		
		glm::vec3 right = glm::normalize(glm::cross(glm::vec3(0, 1, 0), direction));
		glm::vec3 up = glm::cross(direction, right);

		return glm::lookAt(position, direction + position, up);
	}

	glm::mat4 PerspectiveCamera::getProjection(std::shared_ptr<IO::Window> window) {
		auto size = window->getSize();
		float aspectRatio = (float) size.x / (float) size.y;
		return glm::perspective(fov, aspectRatio, 0.01f, 200.0f);
	}

	glm::mat4 OrthoCamera::getProjection(std::shared_ptr<IO::Window> window) {
		glm::ivec2 size = window->getSize();
		return glm::ortho(-size.x / 2.0f, size.x / 2.0f, -size.y / 2.0f, size.y / 2.0f, -100.0f, 100.0f);
	}
}
