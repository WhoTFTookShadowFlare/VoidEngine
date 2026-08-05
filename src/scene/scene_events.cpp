#include "ve/scene/events.hpp"

namespace VoidEngine::Scene::Events {
	const Class EComponentUpdate::ClassData = {
		.name = "EComponentUpdate",
		.super = &Event::AEvent::ClassData
	};

	const Class ESceneDraw::ClassData = {
		.name = "ESceneDraw",
		.super = &Event::AEvent::ClassData
	};

	const Class EComponentDraw::ClassData = {
		.name = "EComponentDraw",
		.super = &Event::AEvent::ClassData
	};

	const Class EAddedToScene::ClassData = {
		.name = "EAddedToScene",
		.super = &Event::AEvent::ClassData
	};

	const Class ERemovedFromScene::ClassData = {
		.name = "ERemovedFromScene",
		.super = &Event::AEvent::ClassData
	};

	const Class EComponentAddedToObject::ClassData = {
		.name = "EComponentAddedToObject",
		.super = &Event::AEvent::ClassData
	};

	const Class EComponentRemovedFromObject::ClassData = {
		.name = "EComponentRemovedFromObject",
		.super = &Event::AEvent::ClassData
	};

	const Class EChildAdded::ClassData = {
		.name = "EChildAdded",
		.super = &Event::AEvent::ClassData
	};

	const Class EChildRemoved::ClassData = {
		.name = "EChildRemoved",
		.super = &Event::AEvent::ClassData
	};
}
