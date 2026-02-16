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
	vector<shared_ptr<ComponentUpdater>> ComponentUpdater::instances = {};

	ComponentUpdater::ComponentUpdater() {}

	void ComponentUpdater::ensureSetup() {
		if(instances.size() == 0)
			instances.resize(max(thread::hardware_concurrency(), (uint32_t) 1));
	}

	shared_ptr<ComponentUpdater> ComponentUpdater::getInstance(uint32_t idx) {
		if(instances.size() == 0) {
			uint32_t maxUpdaters = std::max(thread::hardware_concurrency(), (uint32_t) 1);
			instances.resize(maxUpdaters);
		}
		if(instances[idx % instances.size()] == nullptr) instances[idx % instances.size()] = shared_ptr<ComponentUpdater>(new ComponentUpdater);
		return instances[idx % instances.size()];
	}

	uint32_t ComponentUpdater::getInstanceCount() {
		return instances.size();
	}

	bool ComponentUpdater::isComponentUpdating(shared_ptr<AObjectComponent> component) {
		for(const auto& updater : instances) {
			if(updater == nullptr) continue;
			if(updater->handlesComponent(component)) return true;
		}
		return false;
	}

	void ComponentUpdater::cleanComponents() {
		for(auto comp = components.end(); comp != components.begin(); comp--) {
			if(comp->expired()) {
				iter_swap(comp, components.end());
				components.pop_back();
			}
		}
	}

	bool ComponentUpdater::handlesComponent(shared_ptr<AObjectComponent> comp) {
		return find_if(components.begin(), components.end(), [&comp](const auto& updated) {
			return comp == updated.lock();
		}) != components.end();
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
		for(auto comp : components) {
			if(comp.expired()) {
				needsCleanup = true;
				continue;
			}
			if(auto component = comp.lock()) component->update(delta);
		}
		if(needsCleanup) cleanComponents();
	}
}

