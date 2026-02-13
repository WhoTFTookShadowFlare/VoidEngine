#include "ve/scene/component_updater.hpp"
#include "ve/scene/object_component.hpp"
#include <memory>
#include <vector>

namespace VoidEngine::Scene {
	shared_ptr<ComponentUpdater> ComponentUpdater::instance = nullptr;

	ComponentUpdater::ComponentUpdater() {}

	shared_ptr<ComponentUpdater> ComponentUpdater::getInstance() {
		if(instance == nullptr) instance = shared_ptr<ComponentUpdater>(new ComponentUpdater);
		return instance;
	}

	void ComponentUpdater::cleanComponents() {
		for(auto comp = components.end(); comp != components.begin(); comp--) {
			if(comp->expired()) {
				comp->swap(components.back());
				components.pop_back();
			}
		}
	}

	void ComponentUpdater::addComponent(std::weak_ptr<AObjectComponent> comp) {
		components.push_back(comp);
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

