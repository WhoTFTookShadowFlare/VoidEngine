#include "ve/scene/object_component.hpp"
#include <algorithm>
#include <memory>
#include <print>
#include <vector>

#include "ve/class_db.hpp"
#include "ve/class_methods.hpp"
#include "ve/scene/game_object.hpp"
#include "ve/variant.hpp"

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

	Variant AObjectComponent::scr_getObjectsUsing(std::vector<Variant> args) {
		if(args.size() != 0) std::println("[WARN] Expected 0 args for getObjectsUsing");
		auto objs = getObjectsUsing();
		std::vector<Variant> objVars;
		std::for_each(objs.begin(), objs.end(), [&](std::shared_ptr<GameObject>& obj) {
			objVars.push_back(Variant(obj));
		});
		return objVars;
	}

	const Class AObjectComponent::ClassData = {
		.name = "AObjectComponent",
		.super = &Object::ClassData,
		.methods = {
			new NativeMethod("getObjectsUsing", &AObjectComponent::scr_getObjectsUsing)
		}
	};
}

