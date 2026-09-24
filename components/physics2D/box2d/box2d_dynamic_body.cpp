#include <box2d_dynamic_body.hpp>

#include <_box2d_body_shared.hpp>

namespace VoidEngine::Physics2D::Box2D {
	Box2DDynamicBody::Box2DDynamicBody(b2WorldId world) {
		b2BodyDef def = b2DefaultBodyDef();
		def.type = b2_dynamicBody;
		body = b2CreateBody(world, &def);
	}
	
	Box2DDynamicBody::~Box2DDynamicBody() {
		b2DestroyBody(body);
	}

	void Box2DDynamicBody::updateShapes() {
		auto shapes = getShapes();
		updateBodyShape(body, shapes);
	}

	glm::vec2 Box2DDynamicBody::getPosition() const {
		return getBodyPosition(body);
	}
	
	float Box2DDynamicBody::getRotation() const {
		return getBodyRotation(body);
	}

	void Box2DDynamicBody::setPosition(glm::vec2 value) {
		setBodyPosition(body, value);
	}
	
	void Box2DDynamicBody::setRotation(float value) {
		setBodyRotation(body, value);
	}
}
