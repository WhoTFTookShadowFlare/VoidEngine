#include <ve/physics2d/a_body_2d.hpp>

namespace VoidEngine::Physics2D {
	void ABody2D::setShapes(std::vector<std::shared_ptr<ResourceProviders::Shape2D::A2DShapeProvider>> value) {
		shapes = value;
		updateShapes();
	}

	std::vector<std::shared_ptr<ResourceProviders::Shape2D::A2DShapeProvider>> ABody2D::getShapes() {
		return shapes;
	}
}
