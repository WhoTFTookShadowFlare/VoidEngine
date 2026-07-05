#include "ve/scene/object_component.hpp"
#include <algorithm>
#include <memory>
#include <vector>

#include "ve/class_db.hpp"

namespace VoidEngine::Scene {
	void AObjectComponent::cleanTiedTo() {
		tiedTo.resize(std::distance(
			tiedTo.begin(),
			std::remove_if(tiedTo.begin(), tiedTo.end(), [](auto& obj) {
				return obj.lock() == nullptr;
			})
		));
	}

	std::vector<std::shared_ptr<GameObject>> AObjectComponent::getObjectsUsing() {
		cleanTiedTo();
		std::vector<std::shared_ptr<GameObject>> retVal(tiedTo.size());
		std::transform(tiedTo.begin(), tiedTo.end(), retVal.begin(),
				[](std::weak_ptr<GameObject>& obj) { return obj.lock(); });
		return retVal;
	}

	const Class AObjectComponent::ClassData = {
		.name = "AObjectComponent",
	};
}

