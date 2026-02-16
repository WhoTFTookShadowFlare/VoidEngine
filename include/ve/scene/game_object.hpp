#pragma once

#include "ve/scene/object_component.hpp"
#include <memory>
#include <vector>

namespace VoidEngine::Scene {
	using namespace std;
	class GameObject final : public enable_shared_from_this<GameObject> {
		vector<shared_ptr<AObjectComponent>> components = {};
	public:
		
		void addComponent(shared_ptr<AObjectComponent> component);
		vector<shared_ptr<AObjectComponent>> getComponents();
		void removeComponent(shared_ptr<AObjectComponent> component);

		void draw(double delta);
	};
}

