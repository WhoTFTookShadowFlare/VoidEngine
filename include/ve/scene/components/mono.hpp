#pragma once

#include "ve/scene/object_component.hpp"
#include <mono-2.0/mono/metadata/object-forward.h>

namespace VoidEngine::Scene::Components {
	class MonoComponent : public AObjectComponent {
		MonoObject *inst = nullptr;
		MonoClass *instClass = nullptr;

		MonoMethod *updateFunc = nullptr;
		MonoMethod *drawFunc = nullptr;
	public:
		MonoComponent(MonoObject*);
		
		void update(double delta);
		void draw(double delta);
	};
}

