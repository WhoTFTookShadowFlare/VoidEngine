#pragma once

#include <ve/scene/components/a_object_component.hpp>

namespace VoidEngine::Scene {
	class GameObject;
}

namespace VoidEngine::Scene::Components {
	class APolyObjectComponent : public AObjectComponent {
		friend class GameObject;
		VE_CLASS(APolyObjectComponent);
	private:
		std::vector<std::weak_ptr<GameObject>> objects;

		Variant scr_getObjects(void) const;
	public:
		std::vector<std::shared_ptr<GameObject>> getObjects() const;
	};
}
