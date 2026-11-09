#pragma once

#include <ve/scene/components/a_object_component.hpp>

namespace VoidEngine::Scene {
	class GameObject;
	class Scene;
}

namespace VoidEngine::Scene::Components {
	class APolyObjectComponent : public AObjectComponent {
		friend class GameObject;
		friend class Scene;
		VE_CLASS(APolyObjectComponent);
	private:
		std::vector<std::weak_ptr<GameObject>> objects;
		std::weak_ptr<Scene> scene;

		Variant scr_getObjects(void) const;

		Variant scr_isBoundToScene(std::vector<Variant>);
		Variant scr_isBoundToAnyScene(std::vector<Variant>);
	public:
		std::vector<std::shared_ptr<GameObject>> getObjects() const;

		bool isBoundToScene(std::shared_ptr<Scene>) const;
		bool isBoundToAnyScene() const;
	};
}
