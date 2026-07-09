#include "ve/scene/ui/ui_element.hpp"

#include "ve/scene/ui/ui_draw.hpp"
#include <algorithm>

namespace VoidEngine::Scene {
	const Class UIElement::ClassData = { .name = "UIElement" };

	void UIElement::draw(Events::ESceneDraw& drawEvt) {
		Events::EUIDraw evt(drawEvt.delta, drawEvt.target, drawEvt.scene, parent.lock());
		onDraw(evt);

		std::for_each(children.begin(), children.end(), [&drawEvt](auto& entry) {
			entry.second->draw(drawEvt);
		});
	}
}
