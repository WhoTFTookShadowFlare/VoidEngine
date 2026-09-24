#include <_box2d_body_shared.hpp>

namespace VoidEngine::Physics2D::Box2D {
	void updateBodyShape(b2BodyId body, std::vector<std::shared_ptr<ResourceProviders::Shape2D::A2DShapeProvider>>& shapes) {
		const int cntShapesToRemove = b2Body_GetShapeCount(body);
		std::vector<b2ShapeId> shapesToRemove(cntShapesToRemove);
		b2Body_GetShapes(body, shapesToRemove.data(), cntShapesToRemove);
		for(const auto& shape : shapesToRemove) {
			b2DestroyShape(shape, false);
		}

		for(const auto& shape : shapes) {
			b2ShapeDef shapeDef = b2DefaultShapeDef();

			const auto rawPoints = shape->getPoints();
			const b2Vec2* points = reinterpret_cast<const b2Vec2*>(rawPoints.data());
			b2Hull hull = b2ComputeHull(points, rawPoints.size());
			b2Polygon polygon = b2MakePolygon(&hull, 0);
			b2CreatePolygonShape(body, &shapeDef, &polygon);
		}
	}
	
	glm::vec2 getBodyPosition(b2BodyId body) {
		b2Pos position = b2Body_GetPosition(body);
		return *reinterpret_cast<glm::vec2*>(&position);
	}

	float getBodyRotation(b2BodyId body) {
		return b2Rot_GetAngle(b2Body_GetRotation(body));
	}

	void setBodyPosition(b2BodyId body, glm::vec2 position) {
		b2Body_SetTransform(body, *reinterpret_cast<b2Pos*>(&position), b2Body_GetRotation(body));
	}

	void setBodyRotation(b2BodyId body, float rotation) {
		b2Body_SetTransform(body, b2Body_GetPosition(body), b2MakeRot(rotation));
	}
}