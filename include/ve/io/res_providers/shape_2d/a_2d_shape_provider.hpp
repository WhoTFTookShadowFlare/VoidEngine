#pragma once

#include <vector>
#include <glm/ext/vector_float2.hpp>

namespace VoidEngine::ResourceProviders::Shape2D {
	class A2DShapeProvider {
	public:
		virtual std::vector<glm::vec2> getPoints() const = 0;
	};
}