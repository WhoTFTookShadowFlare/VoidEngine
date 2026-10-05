#include <box2d_world.hpp>

#include <box2d_static_body.hpp>
#include <box2d_dynamic_body.hpp>
#include <box2d_kinematic_body.hpp>

namespace VoidEngine::Physics2D::Box2D {
	Box2DWorld::Box2DWorld() {
		b2WorldDef def = b2DefaultWorldDef();
		world = b2CreateWorld(&def);
	}

	Box2DWorld::~Box2DWorld() {
		b2DestroyWorld(world);
	}

	void Box2DWorld::stepSimulation(double delta) {
		b2World_Step(world, delta, getSubstepCount());
	}

	std::shared_ptr<AStaticBody2D> Box2DWorld::createStaticBody() {
		return std::shared_ptr<AStaticBody2D>(new Box2DStaticBody(world));
	}

	std::shared_ptr<ADynamicBody2D> Box2DWorld::createDynamicBody() {
		return std::shared_ptr<ADynamicBody2D>(new Box2DDynamicBody(world));
	}

	std::shared_ptr<AKinematicBody2D> Box2DWorld::createKinematicBody() {
		return std::shared_ptr<AKinematicBody2D>(new Box2DKinematicBody(world));
	}
}
