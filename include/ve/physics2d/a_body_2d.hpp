#pragma once

#include <vector>
#include <memory>

#include <ve/io/res_providers/shape_2d/a_2d_shape_provider.hpp>

namespace VoidEngine::Physics2D {
	class ABody2D {
	private:
		std::vector<std::shared_ptr<ResourceProviders::Shape2D::A2DShapeProvider>> shapes;
	protected:
		virtual void updateShapes() = 0;
	public:
		virtual ~ABody2D() = default;

		void setShapes(std::vector<std::shared_ptr<ResourceProviders::Shape2D::A2DShapeProvider>>);
		std::vector<std::shared_ptr<ResourceProviders::Shape2D::A2DShapeProvider>> getShapes();

		virtual glm::vec2 getPosition() const = 0;
		virtual float getRotation() const = 0;

		virtual void setPosition(glm::vec2) = 0;
		virtual void setRotation(float) = 0;
	};
}