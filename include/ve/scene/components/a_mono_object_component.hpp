#pragma once

#include <ve/scene/components/a_object_component.hpp>

namespace VoidEngine::Scene {
    class GameObject;
}

namespace VoidEngine::Scene::Components {
    class AMonoObjectComponent : public AObjectComponent {
        friend class GameObject;
        VE_CLASS(AMonoObjectComponent);
    private:
        std::weak_ptr<GameObject> object;

        Variant scr_getObject(void) const;
    public:
        std::shared_ptr<GameObject> getObject() const;
    };
}
