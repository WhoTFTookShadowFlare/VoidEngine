#pragma once

#include <ve/physics2d/a_kinematic_body_2d.hpp>
#include <box2d/box2d.h>

namespace VoidEngine::Physics2D::Box2D {
	class Box2DKinematicBody final : public AKinematicBody2D {
	private:
		b2BodyId body;
	public:
		Box2DKinematicBody(b2WorldId);
		~Box2DKinematicBody();

		void updateShapes();

		glm::vec2 getPosition() const;
		float getRotation() const;

		void setPosition(glm::vec2);
		void setRotation(float);
	};
}
