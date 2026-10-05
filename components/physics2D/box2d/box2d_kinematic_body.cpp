#include <box2d_kinematic_body.hpp>
#include <_box2d_body_shared.hpp>

namespace VoidEngine::Physics2D::Box2D {
	Box2DKinematicBody::Box2DKinematicBody(b2WorldId world) {
		b2BodyDef def = b2DefaultBodyDef();
		def.type = b2_kinematicBody;
		body = b2CreateBody(world, &def);
	}
	
	Box2DKinematicBody::~Box2DKinematicBody() {
		b2DestroyBody(body);
	}

	void Box2DKinematicBody::updateShapes() {
		auto shapes = getShapes();
		updateBodyShape(body, shapes);
	}
	
	glm::vec2 Box2DKinematicBody::getPosition() const {
		return getBodyPosition(body);
	}

	float Box2DKinematicBody::getRotation() const {
		return getBodyRotation(body);
	}

	void Box2DKinematicBody::setPosition(glm::vec2 value) {
		setBodyPosition(body, value);
	}
	
	void Box2DKinematicBody::setRotation(float value) {
		setBodyRotation(body, value);
	}
}
