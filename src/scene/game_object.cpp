#include "ve/scene/game_object.hpp"
#include "ve/scene/object_component.hpp"
#include <memory>

namespace VoidEngine::Scene {
	void GameObject::addComponent(shared_ptr<AObjectComponent> comp) {
		components.push_back(comp);
	}

	void GameObject::removeComponent(shared_ptr<AObjectComponent> comp) {
		std::erase_if(components, [&comp](shared_ptr<AObjectComponent> iterEntry) {
			return iterEntry == comp;
		});
	}

	vector<shared_ptr<AObjectComponent>> GameObject::getComponents() {
		return components;
	}

	void GameObject::draw(double delta) {
		for(auto& comp : components) comp->draw(delta);
	}
}

