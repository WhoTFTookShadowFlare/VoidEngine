#pragma once

#include <glm/ext/vector_float2.hpp>
#include <glm/ext/vector_float3.hpp>
#include <glm/ext/vector_float4.hpp>

namespace VoidEngine::IO::GFX {
	struct Vertex {
		glm::vec3 position;
		glm::vec4 color;
		glm::vec2 UV;
		glm::vec3 normal;
	};
}

