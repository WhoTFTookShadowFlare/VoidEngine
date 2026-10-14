#include "ve/class_db.hpp"

#include "ve/engine_events.hpp"
#include "ve/event/event.hpp"
#include "ve/io/res_providers/mesh/a_provider.hpp"
#include "ve/io/res_providers/texture/a_provider.hpp"
#include "ve/io/window_events.hpp"
#include "ve/object.hpp"

#include "ve/scene/scene.hpp"
#include "ve/scene/game_object.hpp"
#include "ve/scene/components/a_object_component.hpp"
#include "ve/scene/components/a_mono_object_component.hpp"
#include "ve/scene/components/a_poly_object_component.hpp"

namespace VoidEngine {
	std::shared_ptr<ClassDB> ClassDB::instance = nullptr;

	void ClassDB::freezeClassList() {
		classListFrozen = true;
	}

	ClassDB::ClassDB() {
		registerClass(&Object::ClassData);

		registerClass(&Event::AEvent::ClassData);

		registerClass(&IO::ResourceProviders::EMeshProviderChanged::ClassData);
		registerClass(&IO::ResourceProviders::ETextureChanged::ClassData);

		registerClass(&Events::EQuitEvent::ClassData);
		registerClass(&Events::EScreenLayoutChangedEvent::ClassData);

		registerClass(&IO::Events::AWindowEvent::ClassData);
		registerClass(&IO::Events::EWindowMinimized::ClassData);
		registerClass(&IO::Events::EWindowRestored::ClassData);
		registerClass(&IO::Events::EWindowMaximized::ClassData);
		registerClass(&IO::Events::EWindowCloseRequested::ClassData);
		registerClass(&IO::Events::EWindowSizeChanged::ClassData);
		registerClass(&IO::Events::EWindowRepositioned::ClassData);
		registerClass(&IO::Events::EMouseEnter::ClassData);
		registerClass(&IO::Events::EWindowFocus::ClassData);

		registerClass(&IO::Events::WindowCloseRequestedDefaultHandler::ClassData);

		registerClass(&Scene::EObjectRenamed::ClassData);
		registerClass(&Scene::EChildAdded::ClassData);
		registerClass(&Scene::EParented::ClassData);
		registerClass(&Scene::EChildRemoved::ClassData);
		registerClass(&Scene::EAddedToScene::ClassData);
		registerClass(&Scene::ERemovedFromScene::ClassData);

		registerClass(&Scene::Scene::ClassData);
		registerClass(&Scene::GameObject::ClassData);

		registerClass(&Scene::Components::AObjectComponent::ClassData);
		registerClass(&Scene::Components::AMonoObjectComponent::ClassData);
		registerClass(&Scene::Components::APolyObjectComponent::ClassData);
	}

	std::shared_ptr<ClassDB> ClassDB::getInstance() {
		if(instance == nullptr) instance = std::shared_ptr<ClassDB>(new ClassDB);
		return instance;
	}

	const Class* ClassDB::getClassByName(std::string name) {
		return componentClasses[name];
	}

	void ClassDB::registerClass(const Class* cls) {
		if(componentClasses[cls->name] != nullptr) [[unlikely]] {
			std::println("[ERR] Duplicate class name {}", cls->name);
			return;
		}

		if(cls->super == nullptr && cls != &Object::ClassData) [[unlikely]] {
			std::println("[ERR] {} did not setup ClassData::super", cls->getName());
			return;
		}

		if(cls->super != nullptr && cls->super->isFinal()) {
			std::println("[FATAL] {} inherits a class ({}) flagged as final", cls->getName(), cls->super->getName());
			assert(false);
		}

		if(cls->isFinal() && cls->constructor == nullptr) {
			std::println("[WARN] Class {}, is final with no constructor", cls->getName());
		}

		componentClasses[cls->name] = cls;
	}
}
