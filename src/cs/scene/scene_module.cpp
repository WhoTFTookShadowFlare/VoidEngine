#include "ve/cs/interface.hpp"
#include "ve/cs/scene/module.hpp"
#include "ve/scene/components/mono.hpp"
#include "ve/scene/components/transform.hpp"
#include "ve/scene/game_object.hpp"
#include "ve/scene/object_component.hpp"
#include "ve/scene/scene.hpp"
#include <format>
#include <glm/ext/matrix_float4x4.hpp>
#include <memory>
#include <mono-2.0/mono/metadata/class.h>
#include <mono-2.0/mono/metadata/loader.h>
#include <mono-2.0/mono/metadata/object-forward.h>
#include <mono-2.0/mono/metadata/object.h>
#include <mono-2.0/mono/metadata/exception.h>

namespace VoidEngine::CS::Scene {
	using namespace std;

	void Scene_ctor(MonoObject*);
	void Scene_finalize(MonoObject*);
	void Scene_set_Item(MonoObject*, MonoString*, MonoObject*);
	MonoObject *Scene_get_Item(MonoObject*, MonoString*);
	void Scene_Draw(MonoObject*, double);

	void GameObject_ctor(MonoObject*);
	void GameObject_finalize(MonoObject*);
	void GameObject_AddComponent(MonoObject*, MonoObject*);
	MonoArray *GameObject_GetComponents(MonoObject*);
	void GameObject_RemoveComponent(MonoObject*, MonoObject*);

	void AObjectComponent_ctor(MonoObject*);
	void AObjectComponent_finalize(MonoObject*);

	void TransformComponent_ctor(MonoObject*);
	void TransformComponent_finalize(MonoObject*);
	glm::mat4 TransformComponent_GetMatrix(MonoObject*);

	MonoClass *sceneClass = nullptr, *gameObjectClass = nullptr, *objectComponentClass = nullptr;
	MonoClass *transformComponentClass = nullptr;

	CSharpInterface *interface = nullptr;

	void initModule_Engine_Scene() {
		mono_add_internal_call("VoidEngine.Scene.Scene::.ctor", (void*) Scene_ctor);
		mono_add_internal_call("VoidEngine.Scene.Scene::Finalize", (void*) Scene_finalize);
		mono_add_internal_call("VoidEngine.Scene.Scene::set_Item", (void*) Scene_set_Item);
		mono_add_internal_call("VoidEngine.Scene.Scene::get_Item", (void*) Scene_get_Item);
		mono_add_internal_call("VoidEngine.Scene.Scene::Draw", (void*) Scene_Draw);

		mono_add_internal_call("VoidEngine.Scene.GameObject::.ctor", (void*) GameObject_ctor);
		mono_add_internal_call("VoidEngine.Scene.GameObject::Finalize", (void*) GameObject_finalize);
		mono_add_internal_call("VoidEngine.Scene.GameObject::AddComponent", (void*) GameObject_AddComponent);
		mono_add_internal_call("VoidEngine.Scene.GameObject::GetComponents", (void*) GameObject_GetComponents);

		mono_add_internal_call("VoidEngine.Scene.AObjectComponent::.ctor", (void*) AObjectComponent_ctor);
		mono_add_internal_call("VoidEngine.Scene.AObjectComponent::Finalize", (void*) AObjectComponent_finalize);

		mono_add_internal_call("VoidEngine.Scene.Components.TransformComponent::.ctor", (void*) TransformComponent_ctor);
		mono_add_internal_call("VoidEngine.Scene.Components.TransformComponent::Finalize", (void*) TransformComponent_finalize);
		mono_add_internal_call("VoidEngine.Scene.Components.TransformComponent::GetMatrix", (void*) TransformComponent_GetMatrix);

		interface = CSharpInterface::getInstance();

		sceneClass = interface->getClass("VoidEngine.Scene", "Scene");
		gameObjectClass = interface->getClass("VoidEngine.Scene", "GameObject");
		objectComponentClass = interface->getClass("VoidEngine.Scene", "AObjectComponent");

		transformComponentClass = interface->getClass("VoidEngine.Scene.Components", "TransformComponent");
	}

	MonoClass *getSceneClass(void) { return sceneClass; }
	MonoClass *getGameObjectClass(void) { return gameObjectClass; }
	MonoClass *getAObjectComponentClass(void) { return objectComponentClass; }
	MonoClass *getTransformComponentClass(void) { return transformComponentClass; }

	void Scene_ctor(MonoObject *self) {
		if(self == nullptr) {
			mono_raise_exception(mono_get_exception_null_reference());
			return;
		}

		MonoClassField *cxxObject = mono_class_get_field_from_name(sceneClass, "cxxObject");
		shared_ptr<VoidEngine::Scene::Scene> *scn = new shared_ptr<VoidEngine::Scene::Scene>(new VoidEngine::Scene::Scene());
		mono_field_set_value(self, cxxObject, &scn);
	}

	void Scene_finalize(MonoObject *self) {
		if(self == nullptr) {
			mono_raise_exception(mono_get_exception_null_reference());
			return;
		}

		MonoClassField *cxxObject = mono_class_get_field_from_name(sceneClass, "cxxObject");
		shared_ptr<VoidEngine::Scene::Scene> *scn = nullptr;
		mono_field_get_value(self, cxxObject, &scn);
		if(scn != nullptr) delete scn;
	}

	void Scene_set_Item(MonoObject *self, MonoString *objName, MonoObject *gameObject) {
		if(self == nullptr || objName == nullptr || gameObject == nullptr) {
			mono_raise_exception(mono_get_exception_null_reference());
			return;
		}

		MonoClassField *cxxObject = mono_class_get_field_from_name(sceneClass, "cxxObject");
		shared_ptr<VoidEngine::Scene::Scene> *scn = nullptr;
		mono_field_get_value(self, cxxObject, &scn);
		
		MonoClassField *objCxxObject = mono_class_get_field_from_name(getGameObjectClass(), "cxxObject");
		shared_ptr<VoidEngine::Scene::GameObject> *obj = nullptr;
		mono_field_get_value(gameObject, objCxxObject, &obj);

		string nameStr = mono_string_to_utf8(objName);

		(**scn)[nameStr] = shared_ptr<VoidEngine::Scene::GameObject>(*obj);
	}

	MonoObject *Scene_get_Item(MonoObject *self, MonoString *objName) {
		if(self == nullptr || objName == nullptr) {
			mono_raise_exception(mono_get_exception_null_reference());
			return nullptr;
		}

		MonoClassField *cxxObject = mono_class_get_field_from_name(sceneClass, "cxxObject");
		shared_ptr<VoidEngine::Scene::Scene> *scn = nullptr;
		mono_field_get_value(self, cxxObject, &scn);

		string nameStr = mono_string_to_utf8(objName);

		shared_ptr<VoidEngine::Scene::GameObject>& obj = (*scn->get())[nameStr];
		if(obj != nullptr) {
			MonoObject *csObj = interface->allocClass(getGameObjectClass());
			MonoClassField *gameObjectCxxObject = mono_class_get_field_from_name(getGameObjectClass(), "cxxObject");
			shared_ptr<VoidEngine::Scene::GameObject> *objPtr = new shared_ptr<VoidEngine::Scene::GameObject>(obj);
			mono_field_set_value(csObj, gameObjectCxxObject, &objPtr);
		}

		return nullptr;
	}

	void Scene_Draw(MonoObject *self, double delta) {
		if(self == nullptr) {
			mono_raise_exception(mono_get_exception_null_reference());
			return;
		}

		MonoClassField *cxxObject = mono_class_get_field_from_name(sceneClass, "cxxObject");
		shared_ptr<VoidEngine::Scene::Scene> *scn = nullptr;
		mono_field_get_value(self, cxxObject, &scn);
		if(scn != nullptr) (*scn)->draw(delta);
	}

	void GameObject_ctor(MonoObject *self) {
		if(self == nullptr) {
			mono_raise_exception(mono_get_exception_null_reference());
			return;
		}

		MonoClassField *cxxObject = mono_class_get_field_from_name(getGameObjectClass(), "cxxObject");
		shared_ptr<VoidEngine::Scene::GameObject> *obj = new shared_ptr<VoidEngine::Scene::GameObject>(new VoidEngine::Scene::GameObject);
		mono_field_set_value(self, cxxObject, &obj);
	}

	void GameObject_finalize(MonoObject *self) {
		if(self == nullptr) {
			mono_raise_exception(mono_get_exception_null_reference());
			return;
		}

		MonoClassField *cxxObject = mono_class_get_field_from_name(getGameObjectClass(), "cxxObject");
		shared_ptr<VoidEngine::Scene::GameObject> *obj = nullptr;
		mono_field_get_value(self, cxxObject, &obj);
		if(obj != nullptr) delete obj;
	}

	void GameObject_AddComponent(MonoObject *self, MonoObject *component) {
		if(self == nullptr || component == nullptr) {
			mono_raise_exception(mono_get_exception_null_reference());
			return;
		}

		MonoClass *compClass = mono_object_get_class(component);
		if(!mono_class_is_subclass_of(compClass, getAObjectComponentClass(), false)) {
			mono_raise_exception(mono_get_exception_invalid_cast());
			return;
		}

		MonoClassField *cxxObject = mono_class_get_field_from_name(getGameObjectClass(), "cxxObject");
		shared_ptr<VoidEngine::Scene::GameObject> *obj = nullptr;
		mono_field_get_value(self, cxxObject, &obj);

		MonoClassField *componentCxxObject = mono_class_get_field_from_name(getAObjectComponentClass(), "cxxObject");
		shared_ptr<VoidEngine::Scene::AObjectComponent> *comp = nullptr;
		mono_field_get_value(component, componentCxxObject, &comp);

		(*obj)->addComponent(*comp);
	}

	MonoArray *GameObject_GetComponents(MonoObject *self) {
		if(self == nullptr) {
			mono_raise_exception(mono_get_exception_null_reference());
			return nullptr;
		}

		MonoClassField *cxxObject = mono_class_get_field_from_name(getGameObjectClass(), "cxxObject");
		shared_ptr<VoidEngine::Scene::GameObject> *obj = nullptr;
		mono_field_get_value(self, cxxObject, &obj);

		auto comps = (*obj)->getComponents();

		MonoArray *arr = interface->allocArray(getAObjectComponentClass(), comps.size());

		MonoClassField *compCxxObject = mono_class_get_field_from_name(getAObjectComponentClass(), "cxxObject");

		for(size_t idx = 0; idx < comps.size(); idx++) {
			const auto& comp = comps[idx];
			MonoClass *toSetup = getAObjectComponentClass();
			
			auto monoComp = dynamic_cast<VoidEngine::Scene::Components::MonoComponent*>(comp.get());
			if(monoComp != nullptr) {
				mono_array_set(arr, MonoObject*, idx, monoComp->getObject());
				continue;
			}
			MonoClass *compCls = comp->getCSClass();
			if(compCls == nullptr) {
				mono_raise_exception(mono_get_exception_not_implemented(format("Native class {} does not have a C# equivalent", typeid(comp.get()).name()).c_str()));
				return nullptr;
			}
			MonoObject *csComp = interface->allocClass(comp->getCSClass());
			
			auto ptr = new shared_ptr<VoidEngine::Scene::AObjectComponent>(comp);
			mono_field_set_value(csComp, compCxxObject, &ptr);
			mono_array_set(arr, MonoObject*, idx, csComp);
		}

		return arr;
	}

	void GameObject_RemoveComponent(MonoObject *self, MonoObject *compToRemove) {
		if(self == nullptr || compToRemove == nullptr)  {
			mono_raise_exception(mono_get_exception_null_reference());
			return;
		}

		MonoClassField *cxxObject = mono_class_get_field_from_name(getGameObjectClass(), "cxxObject");
		shared_ptr<VoidEngine::Scene::GameObject> *obj = nullptr;
		mono_field_get_value(self, cxxObject, &obj);

		MonoClassField *compCxxObject = mono_class_get_field_from_name(getAObjectComponentClass(), "cxxObject");
		shared_ptr<VoidEngine::Scene::AObjectComponent> *comp = nullptr;
		mono_field_get_value(compToRemove, compCxxObject, &comp);

		(*obj)->removeComponent(*comp);
	}

	void AObjectComponent_ctor(MonoObject *self) {
		if(self == nullptr) {
			mono_raise_exception(mono_get_exception_null_reference());
			return;
		}

		MonoClassField *cxxObject = mono_class_get_field_from_name(getAObjectComponentClass(), "cxxObject");
		shared_ptr<VoidEngine::Scene::Components::MonoComponent> *comp = new shared_ptr<VoidEngine::Scene::Components::MonoComponent>(new VoidEngine::Scene::Components::MonoComponent(self));
		mono_field_set_value(self, cxxObject, &comp);
	}

	void AObjectComponent_finalize(MonoObject *self) {
		if(self == nullptr) {
			mono_raise_exception(mono_get_exception_null_reference());
			return;
		}

		MonoClassField *cxxObject = mono_class_get_field_from_name(getAObjectComponentClass(), "cxxObject");
		shared_ptr<VoidEngine::Scene::Components::MonoComponent> *comp = nullptr;
		mono_field_get_value(self, cxxObject, &comp);
		if(comp != nullptr) delete comp;
	}

	void TransformComponent_ctor(MonoObject *self) {
		if(self == nullptr) {
			mono_raise_exception(mono_get_exception_null_reference());
			return;
		}

		MonoClassField *cxxObject = mono_class_get_field_from_name(getAObjectComponentClass(), "cxxObject");
		shared_ptr<VoidEngine::Scene::Components::TransformComponent> *comp = new shared_ptr<VoidEngine::Scene::Components::TransformComponent>(new VoidEngine::Scene::Components::TransformComponent);
		mono_field_set_value(self, cxxObject, &comp);
	}

	void TransformComponent_finalize(MonoObject *self) {
		if(self == nullptr) {
			mono_raise_exception(mono_get_exception_null_reference());
			return;
		}

		MonoClassField *cxxObject = mono_class_get_field_from_name(getAObjectComponentClass(), "cxxObject");
		shared_ptr<VoidEngine::Scene::Components::TransformComponent> *comp = nullptr;
		mono_field_get_value(self, cxxObject, &comp);
		if(comp != nullptr) delete comp;
	}

	glm::mat4 TransformComponent_GetMatrix(MonoObject *self) {
		if(self == nullptr) {
			mono_raise_exception(mono_get_exception_null_reference());
			return glm::mat4(1.0f);
		}

		MonoClassField *cxxObject = mono_class_get_field_from_name(getAObjectComponentClass(), "cxxObject");
		shared_ptr<VoidEngine::Scene::Components::TransformComponent> *comp = nullptr;
		mono_field_get_value(self, cxxObject, &comp);

		return (*comp)->getMatrix();
	}
}

