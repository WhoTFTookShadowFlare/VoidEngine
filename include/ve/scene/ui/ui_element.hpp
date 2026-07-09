#pragma once

#include "ve/event/event_bus.hpp"
#include "ve/math/rect2.hpp"
#include "ve/object.hpp"
#include "ve/scene/events.hpp"
#include <map>
#include <memory>
#include <string>

namespace VoidEngine::Scene {
	namespace Events {	
		class EUIDraw;
	}

	class UIElement : public Object {
	private:
		VoidEngine::Math::Rect2f normalizedArea;

		std::weak_ptr<UIElement> parent;
		std::map<std::string, std::shared_ptr<UIElement>> children;

	public:
		static const Class ClassData;
		virtual const Class* getClass() const { return &ClassData; }

		void draw(Events::ESceneDraw&);
		Event::EventBus<Events::EUIDraw> onDraw;
	};
}
