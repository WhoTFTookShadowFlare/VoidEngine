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
	private:
		std::vector<std::weak_ptr<GameObject>> tiedTo;

		void cleanTiedTo();
		Variant scr_getObjectsUsing(std::vector<Variant>);

	public:
		static const Class ClassData;
		virtual ~AObjectComponent() {}

		Event::EventBusLegacy<Events::EComponentAddedToObject> onComponentAdded;
		Event::EventBusLegacy<Events::EComponentRemovedFromObject> onComponentRemoved;

		Event::EventBusLegacy<Events::EComponentUpdate> onUpdate;
		Event::EventBusLegacy<Events::EComponentDraw> onDraw;

		std::vector<std::shared_ptr<GameObject>> getObjectsUsing();

		virtual const Class* getClass() const { return &ClassData; }
	};
}
