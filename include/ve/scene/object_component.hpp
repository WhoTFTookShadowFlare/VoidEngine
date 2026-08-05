#pragma once

#include <memory>
#include <vector>

#include "ve/event/event_bus.hpp"
#include "ve/object.hpp"
#include "ve/class_db.hpp"
#include "ve/scene/events.hpp"
#include "ve/variant.hpp"

namespace VoidEngine::Scene {
	class GameObject;

	class AObjectComponent : public Object {
		friend class GameObject;
		VE_CLASS(AObjectComponent)
	private:
		std::vector<std::weak_ptr<GameObject>> tiedTo;

		void cleanTiedTo();
		Variant scr_getObjectsUsing(std::vector<Variant>);

	public:
		Event::EventBus onComponentAdded = &Events::EComponentAddedToObject::ClassData;
		Event::EventBus onComponentRemoved = &Events::EComponentRemovedFromObject::ClassData;

		Event::EventBus onUpdate = &Events::EComponentUpdate::ClassData;
		Event::EventBus onDraw = &Events::EComponentDraw::ClassData;

		std::vector<std::shared_ptr<GameObject>> getObjectsUsing();
	};
}
