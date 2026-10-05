#pragma once

#include <memory>
#include <ve/physics2d/a_2d_physics_engine.hpp>

namespace VoidEngine::Physics2D {
	class Physics2D final {
		friend class Engine;
	private:
		static Physics2D* instance;
		A2DPhysicsEngine* engine = nullptr;

		static void initialize();
		void finalize();

		Physics2D();
	public:
		static std::shared_ptr<Physics2D> getInstance();

		std::shared_ptr<APhysics2DWorld> createWorld();
	};
}
