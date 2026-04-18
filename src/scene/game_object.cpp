#include "ve/scene/game_object.hpp"
#include "ve/scene/object_component.hpp"
#include <algorithm>
#include <memory>

#include <iostream>

namespace VoidEngine::Scene {
	void GameObject::addComponent(shared_ptr<AObjectComponent> comp) {
		if(comp == nullptr) return;
		components[comp->getClass()] = comp;
		//components.push_back(comp);
		comp->tiedTo.push_back(weak_from_this());

		Events::EAddedToObject evt(shared_from_this(), comp);
		comp->onComponentAdded(evt);
		onComponentAdded(evt);
	}

	void GameObject::removeComponent(shared_ptr<AObjectComponent> comp) {
		/*components.resize(std::distance(
			components.begin(),
			std::remove_if(components.begin(), components.end(), [&](std::shared_ptr<AObjectComponent> iter) {
				if(comp == iter) {
					Events::ERemovedFromObject evt(shared_from_this(), comp);
					comp->onComponentRemoved(evt);
					onComponentRemoved(evt);
					return true;
				}
				return false;
			})
		));*/
		Events::ERemovedFromObject evt(shared_from_this(), comp);
		components[comp->getClass()]->onComponentRemoved(evt);
		onComponentRemoved(evt);
		components.erase(comp->getClass());
	}

	vector<shared_ptr<AObjectComponent>> GameObject::getComponents() {
		std::vector<std::shared_ptr<AObjectComponent>> compList;
		std::for_each(components.cbegin(), components.cend(), [&compList](const auto& iter) {
			compList.emplace_back(iter.second);
			});
		return compList;
	}

	void GameObject::draw(Events::EComponentDraw& draw) {
		for(auto& comp : components) comp.second->onDraw(draw);
	}
}
