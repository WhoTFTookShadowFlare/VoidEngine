#include "ve/scene/events.hpp"

namespace VoidEngine::Scene::Events {
	const Class EComponentUpdate::ClassData = {
		.name = "EComponentUpdate"
	};

	const Class ESceneDraw::ClassData = {
		.name = "ESceneDraw"
	};

	const Class EComponentDraw::ClassData = {
		.name = "EComponentDraw"
	};

	const Class EAddedToScene::ClassData = {
		.name = "EAddedToScene"
	};

	const Class ERemovedFromScene::ClassData = {
		.name = "ERemovedFromScene"
	};

	const Class EComponentAddedToObject::ClassData = {
		.name = "EComponentAddedToObject"
	};

	const Class EComponentRemovedFromObject::ClassData = {
		.name = "EComponentRemovedFromObject"
	};

	const Class EChildAdded::ClassData = {
		.name = "EChildAdded"
	};

	const Class EChildRemoved::ClassData = {
		.name = "EChildRemoved"
	};
}
