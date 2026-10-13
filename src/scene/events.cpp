#include <ve/scene/events.hpp>
#include <ve/scene/game_object.hpp>
#include <ve/scene/scene.hpp>
#include <ve/class_property.hpp>

namespace VoidEngine::Scene {
	const ::VoidEngine::Class EObjectRenamed::ClassData = {
		.name = "EObjectRenamed",
		.super = &Event::AEvent::ClassData,
		.properties = {
			new NativeProperty("object", &EObjectRenamed::scr_getObject),
			new NativeProperty("oldName", &EObjectRenamed::scr_getOldName)
		},
		.constructor = new NativeConstructor(&EObjectRenamed::create),
		.flags = ClassFlags::FINAL
	};

	std::shared_ptr<EObjectRenamed> EObjectRenamed::create() {
		return std::shared_ptr<EObjectRenamed>(new EObjectRenamed);
	}

	Variant EObjectRenamed::scr_getObject(void) const {
		return std::static_pointer_cast<Object>(getObject());
	}

	Variant EObjectRenamed::scr_getOldName(void) const {
		return getOldName();
	}

	std::shared_ptr<GameObject> EObjectRenamed::getObject() const {
		return obj;
	}

	std::string EObjectRenamed::getOldName() const {
		return oldName;
	}

	bool EObjectRenamed::isSetup() const {
		return obj != nullptr;
	}

	const ::VoidEngine::Class EChildAdded::ClassData = {
		.name = "EChildAdded",
		.super = &Event::AEvent::ClassData,
		.properties = {
			new NativeProperty("getParent", &EChildAdded::scr_getParent),
			new NativeProperty("getChild", &EChildAdded::scr_getChild)
		},
		.constructor = new NativeConstructor(&EChildAdded::create),
		.flags = ClassFlags::FINAL
	};

	Variant EChildAdded::scr_getParent(void) const {
		return Variant(getParent());
	}
	
	Variant EChildAdded::scr_getChild(void) const {
		return Variant(getChild());
	}

	std::shared_ptr<EChildAdded> EChildAdded::create() {
		return std::shared_ptr<EChildAdded>(new EChildAdded);
	}

	std::shared_ptr<GameObject> EChildAdded::getParent() const {
		return parent;
	}
	
	std::shared_ptr<GameObject> EChildAdded::getChild() const {
		return child;
	}

	bool EChildAdded::isSetup() const {
		return parent != nullptr && child != nullptr;
	}

	const ::VoidEngine::Class EParented::ClassData = {
		.name = "EParented",
		.super = &Event::AEvent::ClassData,
		.properties = {
			new NativeProperty("parent", &EParented::scr_getParent),
			new NativeProperty("child", &EParented::scr_getChild),
		},
		.constructor = new NativeConstructor(&EParented::create),
		.flags = ClassFlags::FINAL
	};

	Variant EParented::scr_getParent(void) const {
		return Variant(getParent());
	}

	Variant EParented::scr_getChild(void) const {
		return Variant(getChild());
	}

	 std::shared_ptr<EParented> EParented::create() {
		return std::shared_ptr<EParented>(new EParented);
	}

	std::shared_ptr<GameObject> EParented::getParent() const {
		return parent;
	}
	
	std::shared_ptr<GameObject> EParented::getChild() const {
		return child;
	}

	bool EParented::isSetup() const {
		return parent != nullptr && child != nullptr;
	}

	const ::VoidEngine::Class EChildRemoved::ClassData = {
		.name = "EChildRemoved",
		.super = &Event::AEvent::ClassData,
		.constructor = new NativeConstructor(&EChildRemoved::create),
		.flags = ClassFlags::FINAL
	};

	std::shared_ptr<EChildRemoved> EChildRemoved::create() {
		return std::shared_ptr<EChildRemoved>(new EChildRemoved);
	}

	Variant EChildRemoved::scr_getParent(void) const {
		return Variant(getParent());
	}

	Variant EChildRemoved::scr_getChild(void) const {
		return Variant(getChild());
	}

	std::shared_ptr<GameObject> EChildRemoved::getParent() const {
		return parent;
	}
	
	std::shared_ptr<GameObject> EChildRemoved::getChild() const {
		return child;
	}

	bool EChildRemoved::isSetup() const {
		return parent != nullptr && child != nullptr;
	}

	const ::VoidEngine::Class EAddedToScene::ClassData = {
		.name = "EAddedToScene",
		.super = &Event::AEvent::ClassData,
		.properties = {
			new NativeProperty("scene", &EAddedToScene::scr_getScene)
		},
		.constructor = new NativeConstructor(&EAddedToScene::create),
		.flags = ClassFlags::FINAL
	};

	Variant EAddedToScene::scr_getScene(void) const {
		return Variant(getScene());
	}

	std::shared_ptr<EAddedToScene> EAddedToScene::create() {
		return std::shared_ptr<EAddedToScene>(new EAddedToScene);
	}

	std::shared_ptr<Scene> EAddedToScene::getScene() const {
		return scene;
	}

	bool EAddedToScene::isSetup() const {
		return scene != nullptr;
	}

	const ::VoidEngine::Class ERemovedFromScene::ClassData = {
		.name = "ERemovedFromScene",
		.super = &Event::AEvent::ClassData,
		.properties = {
			new NativeProperty("object", &ERemovedFromScene::scr_getObject)
		},
		.constructor = new NativeConstructor(&ERemovedFromScene::create),
		.flags = ClassFlags::FINAL
	};

	Variant ERemovedFromScene::scr_getObject(void) const {
		return Variant(getObject());
	}

	std::shared_ptr<ERemovedFromScene> ERemovedFromScene::create() {
		return std::shared_ptr<ERemovedFromScene>(new ERemovedFromScene);
	}

	std::shared_ptr<GameObject> ERemovedFromScene::getObject() const {
		return object;
	}

	bool ERemovedFromScene::isSetup() const {
		return object != nullptr;
	}
}
