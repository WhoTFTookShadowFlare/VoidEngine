#pragma once

#include <ve/physics2d/a_static_body_2d.hpp>
#include <ve/physics2d/a_dynamic_body_2d.hpp>
#include <ve/physics2d/a_kinematic_body_2d.hpp>

namespace VoidEngine::Physics2D {
	class APhysics2DWorld {
	private:
		int substepCount = 4;
	public:
		virtual void stepSimulation(double delta) = 0;

		int getSubstepCount();
		void setSubstepCount(int);

		virtual std::shared_ptr<AStaticBody2D> createStaticBody() = 0;
		virtual std::shared_ptr<ADynamicBody2D> createDynamicBody() = 0;
		virtual std::shared_ptr<AKinematicBody2D> createKinematicBody() = 0;
	};
}
