#include "ve/scene/game_object.hpp"
#include "ve/scene/object_component.hpp"
#include <algorithm>
#include <memory>

namespace VoidEngine::Scene {
	void GameObject::addComponent(shared_ptr<AObjectComponent> comp) {
		if(comp == nullptr) return;
		components.push_back(comp);
		comp->tiedTo.push_back(weak_from_this());
	}

	void GameObject::removeComponent(shared_ptr<AObjectComponent> comp) {
		auto location = find_if(components.begin(), components.end(), [&comp](shared_ptr<AObjectComponent> iterEntry) {
				return iterEntry == comp;
				});
		if(location == components.end()) return;
		
		auto forRemoval = *location;
		erase_if(forRemoval->tiedTo, [&](weak_ptr<GameObject> obj) {
				return obj.lock() == shared_from_this();
				});
		iter_swap(location, components.end());
		components.pop_back();
	}

	vector<shared_ptr<AObjectComponent>> GameObject::getComponents() {
		return components;
	}

	void GameObject::draw(double delta) {
		for(auto& comp : components) comp->draw(delta);
	}
}

