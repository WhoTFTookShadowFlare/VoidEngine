#pragma once

#include <ve/object.hpp>
#include <ve/event/event_bus.hpp>
#include <ve/scene/events.hpp>

namespace VoidEngine::Scene::Components {
    class AObjectComponent : public Object {
        VE_CLASS(AObjectComponent);
    private:

    public:
        Event::EventBus onAddedToScene = &EAddedToScene::ClassData;
        Event::EventBus onRemovedFromScene = &ERemovedFromScene::ClassData;

        Event::EventBus onAddedToObject = &EComponentAdded::ClassData;
        Event::EventBus onRemovedFromObject = &EComponentRemoved::ClassData;
    };
}
