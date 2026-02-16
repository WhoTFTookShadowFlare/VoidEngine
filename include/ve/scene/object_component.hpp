#pragma once

#include <memory>
#include <mono-2.0/mono/metadata/object-forward.h>
#include <vector>

namespace VoidEngine::Scene {
	class GameObject;

	class AObjectComponent {
		friend class GameObject;
		std::vector<std::weak_ptr<GameObject>> tiedTo;

		void cleanTiedTo();
	public:
		virtual ~AObjectComponent() {}
		virtual void update(double delta) = 0;
		virtual void draw(double delta) = 0;

		virtual MonoClass *getCSClass() { return nullptr; }

		std::vector<std::shared_ptr<GameObject>> getObjectsUsing();
	};
}

