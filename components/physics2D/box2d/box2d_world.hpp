#pragma once

#include <ve/physics2d/a_world_2d.hpp>

#include <box2d/box2d.h>

namespace VoidEngine::Physics2D::Box2D {
	class Box2DWorld final : public VoidEngine::Physics2D::APhysics2DWorld {
	private:
		b2WorldId world;
	public:
		Box2DWorld();
		~Box2DWorld();

		void stepSimulation(double delta);

		std::shared_ptr<AStaticBody2D> createStaticBody();
		std::shared_ptr<ADynamicBody2D> createDynamicBody();
		std::shared_ptr<AKinematicBody2D> createKinematicBody();
	};
}
