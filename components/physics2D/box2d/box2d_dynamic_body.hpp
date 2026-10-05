#pragma once

#include <ve/physics2d/a_dynamic_body_2d.hpp>

#include <box2d/box2d.h>

namespace VoidEngine::Physics2D::Box2D {
	class Box2DDynamicBody : public ADynamicBody2D {
	private:
		b2BodyId body;
	protected:
		void updateShapes();
	public:
		Box2DDynamicBody(b2WorldId);
		~Box2DDynamicBody();

		glm::vec2 getPosition() const;
		float getRotation() const;

		void setPosition(glm::vec2);
		void setRotation(float);
	};
}
