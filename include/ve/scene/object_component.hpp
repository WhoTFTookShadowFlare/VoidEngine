#pragma once

namespace VoidEngine::Scene {
	class GameObject;

	class AObjectComponent {
	public:
		virtual ~AObjectComponent() {}
		virtual void update(double delta) = 0;
		virtual void draw(double delta) = 0;
	};
}

