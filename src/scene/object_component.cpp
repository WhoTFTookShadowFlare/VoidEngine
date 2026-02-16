#include "ve/scene/object_component.hpp"
#include <algorithm>
#include <memory>
#include <vector>

namespace VoidEngine::Scene {
	void AObjectComponent::cleanTiedTo() {
		for(auto obj = tiedTo.end() - 1; obj != tiedTo.begin(); obj--) {
			if((*obj).expired()) {
				std::iter_swap(obj, tiedTo.end());
				tiedTo.pop_back();
			}
		}
	}

	std::vector<std::shared_ptr<GameObject>> AObjectComponent::getObjectsUsing() {
		cleanTiedTo();
		std::vector<std::shared_ptr<GameObject>> retVal(tiedTo.size());
		std::transform(tiedTo.begin(), tiedTo.end(), retVal.begin(),
				[](std::weak_ptr<GameObject> obj) { return obj.lock(); });
		return retVal;
	}
}

