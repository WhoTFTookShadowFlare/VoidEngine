#pragma once

#include "glm/ext/vector_float3.hpp"
namespace VoidEngine::IO::GFX {
	struct Light {
		glm::vec3 diffuse;
		glm::vec3 specular;
	};

	struct DirectionalLight final : public Light {
		glm::vec3 direction;
	};

	struct PointLight final : public Light {
		glm::vec3 position;

		float constant;
		float linear;
		float quadratic;
	};

	struct SpotLight final : public Light {
		glm::vec3 position;
		glm::vec3 direction;

		float constant;
		float linear;
		float quadratic;

		float cutoffAngle;
		float outerCutoffAngle;
	};
}
