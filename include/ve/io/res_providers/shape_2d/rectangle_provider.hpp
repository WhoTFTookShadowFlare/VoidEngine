#pragma once

#include "ve/io/res_providers/shape_2d/a_2d_shape_provider.hpp"
#include <memory>

namespace VoidEngine::ResourceProviders::Shape2D {
	class RectangleProvider : public A2DShapeProvider {
	private:
		float width = 1.0f, height = 1.0f;
	public:
		static std::shared_ptr<RectangleProvider> create();

		std::vector<glm::vec2> getPoints() const;

		float getWidth() const;
		void setWidth(float);

		float getHeight() const;
		void setHeight(float);
	};
}
