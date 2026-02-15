#pragma once

#include "ve/scene/object_component.hpp"
#include <cstdint>
#include <mono-2.0/mono/metadata/object-forward.h>

namespace VoidEngine::Scene::Components {
	class MonoComponent : public AObjectComponent {
		uint32_t gcHandle = 0;
		MonoClass *instClass = nullptr;

		MonoMethod *updateFunc = nullptr;
		MonoMethod *drawFunc = nullptr;
	public:
		MonoComponent(MonoObject*);
		~MonoComponent();
		
		void update(double delta) override;
		void draw(double delta) override;

		MonoClass *getCSClass() override;

		MonoObject *getObject();
	};
}

