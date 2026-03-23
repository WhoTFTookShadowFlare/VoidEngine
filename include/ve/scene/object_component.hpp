#pragma once

#include <memory>
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

		std::vector<std::shared_ptr<GameObject>> getObjectsUsing();
	};
}

