#pragma once

#include "ve/scene/object_component.hpp"
#include <memory>
#include <vector>

namespace VoidEngine::Scene {
	using namespace std;
	class GameObject final {
		vector<shared_ptr<AObjectComponent>> components = {};
	public:
		
		void addComponent(shared_ptr<AObjectComponent> component);
		void draw(double delta);
	};
}

