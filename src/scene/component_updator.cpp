#include "ve/scene/component_updater.hpp"
#include "ve/scene/object_component.hpp"
#include <algorithm>
#include <cstdint>
#include <format>
#include <iostream>
#include <memory>
#include <thread>
#include <vector>

namespace VoidEngine::Scene {
	shared_ptr<ComponentUpdater> ComponentUpdater::instance = nullptr;

	ComponentUpdater::ComponentUpdater() {}

	void ComponentUpdater::ensureSetup() {
		if(instance == nullptr) instance = shared_ptr<ComponentUpdater>(new ComponentUpdater);
	}

	shared_ptr<ComponentUpdater> ComponentUpdater::getInstance() {
		if(instance == nullptr) instance = shared_ptr<ComponentUpdater>(new ComponentUpdater);
		return instance;
	}

	bool ComponentUpdater::isComponentUpdating(shared_ptr<AObjectComponent> component) {
		return find_if(components.cbegin(), components.cend(), [&component](const auto& updated) {
			return component == updated.lock();
			}) != components.end();
	}

	void ComponentUpdater::cleanComponents() {
		components.resize(distance(
			components.begin(),
			remove_if(components.begin(), components.end(), [](auto& comp) {
				return comp.expired();
			})
		));
	}

	void ComponentUpdater::addComponent(std::weak_ptr<AObjectComponent> comp) {
		components.push_back(comp);
	}

	void ComponentUpdater::removeComponent(shared_ptr<AObjectComponent> comp) {
		const auto compLocation = find_if(components.begin(), components.end(), [&comp](const auto& updated) {
				return comp == updated.lock();
		});
		if(compLocation == components.end()) return;
		iter_swap(compLocation, components.end());
		components.pop_back();
	}

	void ComponentUpdater::updateComponents(double delta) {
		bool needsCleanup = false;
		for_each(components.begin(), components.end(), [&needsCleanup, delta](auto& comp) {
			if(comp.expired()) {
				needsCleanup = true;
				return;
			}
			if(auto component = comp.lock()) component->update(delta);
		});
		if(needsCleanup) cleanComponents();
	}
}
