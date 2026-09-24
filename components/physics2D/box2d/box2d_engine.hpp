#pragma once

#include <ve/physics2d/a_2d_physics_engine.hpp>

namespace VoidEngine::Physics2D::Box2D {
	class Box2DEngine final : public A2DPhysicsEngine {
	public:
		Box2DEngine();

		std::shared_ptr<APhysics2DWorld> createWorld();
	};
}
