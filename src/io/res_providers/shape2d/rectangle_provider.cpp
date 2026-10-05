#include <ve/io/res_providers/shape_2d/rectangle_provider.hpp>

namespace VoidEngine::ResourceProviders::Shape2D {
	static std::shared_ptr<RectangleProvider> create();

	std::vector<glm::vec2> RectangleProvider::getPoints() const {
		return {
			{ -width / 2.0, -height / 2.0 },
			{ -width / 2.0,  height / 2.0 },
			{  width / 2.0,  height / 2.0 },
			{  width / 2.0, -height / 2.0 }
		};
	}

	float RectangleProvider::getWidth() const {
		return width;
	}
	
	void RectangleProvider::setWidth(float value) {
		width = abs(value);
	}

	float RectangleProvider::getHeight() const {
		return height;
	}

	void RectangleProvider::setHeight(float value) {
		height = abs(value);
	}

	std::shared_ptr<RectangleProvider> RectangleProvider::create() {
		return std::shared_ptr<RectangleProvider>(new RectangleProvider);
	}
}
