#pragma once

#include "ve/scene/object_component.hpp"
#include <cstdint>
#include <memory>
#include <vector>

namespace VoidEngine::Scene {
	using namespace std;
	class ComponentUpdater final {
		vector<weak_ptr<AObjectComponent>> components = {};

		static vector<shared_ptr<ComponentUpdater>> instances;
		ComponentUpdater();
	public:
		static void ensureSetup();
		static shared_ptr<ComponentUpdater> getInstance(uint32_t index);
		static uint32_t getInstanceCount();

		static bool isComponentUpdating(shared_ptr<AObjectComponent> component);

		void cleanComponents();
		bool handlesComponent(shared_ptr<AObjectComponent>);
		void addComponent(weak_ptr<AObjectComponent>);
		void removeComponent(shared_ptr<AObjectComponent>);
		void updateComponents(double delta);
	};
}

