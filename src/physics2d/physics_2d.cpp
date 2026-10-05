#include <ve/physics2d/physics_2d.hpp>

#include <physics2d_load_order.hpp>

#include <print>
#include <cassert>

namespace VoidEngine::Physics2D {
	Physics2D* Physics2D::instance = nullptr;

	void Physics2D::initialize() {
		if(instance != nullptr) return;
		instance = new Physics2D;
	}
	
	void Physics2D::finalize() {
		if(engine == nullptr) {
			return;
		}

		delete engine;
	}

	std::shared_ptr<Physics2D> Physics2D::getInstance() {
		return std::shared_ptr<Physics2D>(instance, [](void*) {});
	}

	Physics2D::Physics2D() {
		for(const auto& ldFunc : engineLoaders) {
			A2DPhysicsEngine* engine = ldFunc();
			if(engine == nullptr) continue;

			this->engine = engine;
			break;
		}
	}

	std::shared_ptr<APhysics2DWorld> Physics2D::createWorld() {
		assert(engine != nullptr);
		return engine->createWorld();
	}
}
