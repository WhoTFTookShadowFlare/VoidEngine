#pragma once

#include <box2d/box2d.h>
#include <ve/io/res_providers/shape_2d/a_2d_shape_provider.hpp>

#include <vector>
#include <memory>

namespace VoidEngine::Physics2D::Box2D {
	void updateBodyShape(b2BodyId, std::vector<std::shared_ptr<ResourceProviders::Shape2D::A2DShapeProvider>>&);
	glm::vec2 getBodyPosition(b2BodyId);
	float getBodyRotation(b2BodyId);
	void setBodyPosition(b2BodyId, glm::vec2);
	void setBodyRotation(b2BodyId, float);
}
