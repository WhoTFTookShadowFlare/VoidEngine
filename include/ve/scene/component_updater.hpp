#pragma once

#include "ve/scene/object_component.hpp"
#include <memory>
#include <vector>
namespace VoidEngine::Scene {
	using namespace std;
	class ComponentUpdater final {
		vector<weak_ptr<AObjectComponent>> components = {};

		static shared_ptr<ComponentUpdater> instance;
		ComponentUpdater();
	public:
		static shared_ptr<ComponentUpdater> getInstance();

		void cleanComponents();

		void addComponent(weak_ptr<AObjectComponent>);

		void updateComponents(double delta);
	};
}

