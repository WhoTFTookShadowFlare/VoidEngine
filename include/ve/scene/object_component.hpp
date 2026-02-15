#pragma once

#include <mono-2.0/mono/metadata/object-forward.h>

namespace VoidEngine::Scene {
	class GameObject;

	class AObjectComponent {
	public:
		virtual ~AObjectComponent() {}
		virtual void update(double delta) = 0;
		virtual void draw(double delta) = 0;

		virtual MonoClass *getCSClass() { return nullptr; }
	};
}

