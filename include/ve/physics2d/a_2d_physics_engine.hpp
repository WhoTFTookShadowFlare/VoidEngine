#pragma once

#include <ve/physics2d/a_world_2d.hpp>

#include <memory>

namespace VoidEngine::Physics2D {
	class A2DPhysicsEngine {
	public:
		virtual std::shared_ptr<APhysics2DWorld> createWorld() = 0;
	};
}
