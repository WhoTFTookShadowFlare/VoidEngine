#pragma once

#include <ve/physics2d/a_static_body_2d.hpp>

#include <box2d/box2d.h>

namespace VoidEngine::Physics2D::Box2D {
	class Box2DStaticBody final : public AStaticBody2D {
	private:
		b2BodyId body;
	protected:
		void updateShapes();
	public:
		Box2DStaticBody(b2WorldId);
		~Box2DStaticBody();

		glm::vec2 getPosition() const;
		float getRotation() const;

		void setPosition(glm::vec2);
		void setRotation(float);
	};
}
