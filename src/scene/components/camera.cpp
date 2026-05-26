#include "ve/scene/components/camera.hpp"

#include "glm/ext/matrix_float4x4.hpp"
#include "glm/ext/matrix_transform.hpp"
#include "glm/geometric.hpp"
#include "ve/io/window.hpp"
#include "ve/scene/game_object.hpp"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/rotate_vector.hpp>

namespace VoidEngine::Scene::Components {
	glm::mat4 ACamera::getView(std::shared_ptr<GameObject> obj) {
		if(obj == nullptr) return glm::mat4(1.0f);

		glm::vec3 position = obj->position;
		glm::vec3 direction = 
			glm::rotateZ(
				glm::rotateY(
					glm::rotateX(
						glm::vec3(0, 0, -1),
						obj->rotation.x
					),
					obj->rotation.y
				),
				obj->rotation.z
			);
		
		glm::vec3 right = glm::normalize(glm::cross(glm::vec3(0, 1, 0), direction));
		glm::vec3 up = glm::cross(direction, right);

		return glm::lookAt(position, direction + position, up);
	}

	glm::mat4 PerspectiveCamera::getProjection(std::shared_ptr<IO::Window> window) {
		auto size = window->getSize();
		float aspectRatio = (float) size.x / (float) size.y;
		return glm::perspective(glm::radians(fov), aspectRatio, 0.1f, 200.0f);
	}

	std::shared_ptr<PerspectiveCamera> PerspectiveCamera::create() {
		return std::make_shared<PerspectiveCamera>();
	}

	glm::mat4 OrthoCamera::getProjection(std::shared_ptr<IO::Window> window) {
		glm::ivec2 size = window->getSize();
		return glm::ortho(-size.x / 2.0f, size.x / 2.0f, -size.y / 2.0f, size.y / 2.0f, 0.0f, 200.0f);
	}

	std::shared_ptr<OrthoCamera> OrthoCamera::create() {
		return std::make_shared<OrthoCamera>();
	}

	const ComponentClass ACamera::ClassData = {
		.name = "ACamera"
	};

	const ComponentClass PerspectiveCamera::ClassData = {
		.name = "PerspectiveCamera"
	};

	const ComponentClass OrthoCamera::ClassData = {
		.name = "OrthoCamera"
	};
}
