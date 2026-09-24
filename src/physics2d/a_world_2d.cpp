#include <ve/physics2d/a_world_2d.hpp>

namespace VoidEngine::Physics2D {
	int APhysics2DWorld::getSubstepCount() {
		return substepCount;
	}

	void APhysics2DWorld::setSubstepCount(int value) {
		substepCount = value;
	}
}
