#include "ve/scene/game_object.hpp"
#include "ve/scene/object_component.hpp"

namespace VoidEngine::Scene {
	void GameObject::addComponent(shared_ptr<AObjectComponent> comp) {
		components.push_back(comp);
	}

	void GameObject::draw(double delta) {
		for(auto& comp : components) comp->draw(delta);
	}
}

