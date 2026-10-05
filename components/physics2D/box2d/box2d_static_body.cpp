#include <box2d_static_body.hpp>

#include <_box2d_body_shared.hpp>

namespace VoidEngine::Physics2D::Box2D {
	Box2DStaticBody::Box2DStaticBody(b2WorldId world) {
		b2BodyDef def = b2DefaultBodyDef();
		def.type = b2_staticBody;
		body = b2CreateBody(world, &def);
	}
	
	Box2DStaticBody::~Box2DStaticBody() {
		b2DestroyBody(body);
	}

	void Box2DStaticBody::updateShapes() {
		auto shapes = getShapes();
		updateBodyShape(body, shapes);
	}

	glm::vec2 Box2DStaticBody::getPosition() const {
		return getBodyPosition(body);
	}
	
	float Box2DStaticBody::getRotation() const {
		return getBodyRotation(body);
	}

	void Box2DStaticBody::setPosition(glm::vec2 value) {
		setBodyPosition(body, value);
	}
	
	void Box2DStaticBody::setRotation(float value) {
		setBodyRotation(body, value);
	}
}
