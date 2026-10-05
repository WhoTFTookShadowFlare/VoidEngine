#include <box2d_engine.hpp>

#include <print>

#include <box2d_world.hpp>

namespace VoidEngine::Physics2D::Box2D {
	Box2DEngine::Box2DEngine() {
		
	}

	std::shared_ptr<APhysics2DWorld> Box2DEngine::createWorld() {
		return std::shared_ptr<APhysics2DWorld>(new Box2DWorld);
	}
}
