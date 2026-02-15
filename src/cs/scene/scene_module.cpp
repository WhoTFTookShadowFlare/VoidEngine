#include "ve/cs/interface.hpp"
#include "ve/cs/io/gfx/module.hpp"
#include "ve/cs/scene/module.hpp"
#include "ve/io/gfx/mesh.hpp"
#include "ve/scene/component_updater.hpp"
#include "ve/scene/components/mesh.hpp"
#include "ve/scene/components/mono.hpp"
#include "ve/scene/components/transform.hpp"
#include "ve/scene/game_object.hpp"
#include "ve/scene/object_component.hpp"
#include "ve/scene/scene.hpp"
#include <cstdint>
#include <format>
#include <glm/ext/matrix_float4x4.hpp>
#include <glm/ext/vector_float3.hpp>
#include <memory>
#include <mono-2.0/mono/metadata/class.h>
#include <mono-2.0/mono/metadata/loader.h>
#include <mono-2.0/mono/metadata/object-forward.h>
#include <mono-2.0/mono/metadata/object.h>
#include <mono-2.0/mono/metadata/exception.h>

namespace VoidEngine::CS::Scene {
	using namespace std;
	using namespace VoidEngine::Scene::Components;
	using VoidEngine::Scene::ComponentUpdater;

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

	void ComponentUpdater_finalize(MonoObject*);
	MonoObject *ComponentUpdater_GetInstance(uint32_t);
	uint32_t ComponentUpdater_GetInstanceCount();
	bool ComponentUpdater_IsComponentUpdating(MonoObject*);
	void ComponentUpdater_AddComponent(MonoObject*, MonoObject*);
	void ComponentUpdater_RemoveComponent(MonoObject*, MonoObject*);
	bool ComponentUpdater_HandlesComponent(MonoObject*, MonoObject*);
	void ComponentUpdater_UpdateComponents(MonoObject*, double);

	void AObjectComponent_ctor(MonoObject*);
	void AObjectComponent_finalize(MonoObject*);

	void TransformComponent_ctor(MonoObject*);
	void TransformComponent_finalize(MonoObject*);
	void TransformComponent_set_Position(MonoObject*, glm::vec3);
	glm::vec3 TransformComponent_get_Position(MonoObject*);
	void TransformComponent_set_Rotation(MonoObject*, glm::vec3);
	glm::vec3 TransformComponent_get_Rotation(MonoObject*);
	void TransformComponent_set_Scale(MonoObject*, glm::vec3);
	glm::vec3 TransformComponent_get_Scale(MonoObject*);
	glm::mat4 TransformComponent_GetMatrix(MonoObject*);

	void MeshComponent_ctor(MonoObject*);
	void MeshComponent_finalize(MonoObject*);
	void MeshComponent_set_Transform(MonoObject*, MonoObject*);
	MonoObject *MeshComponent_get_Transform(MonoObject*);
	void MeshComponent_set_Mesh(MonoObject*, MonoObject*);
	MonoObject *MeshComponent_get_Mesh(MonoObject*);
	void MeshComponent_set_Program(MonoObject*, MonoObject*);
	MonoObject *MeshComponent_get_Program(MonoObject*);
	void MeshComponent_Draw(MonoObject*, double);

	MonoClass *sceneClass = nullptr, *gameObjectClass = nullptr, *objectComponentClass = nullptr;
	MonoClass *componentUpdaterClass = nullptr;
	MonoClass *transformComponentClass = nullptr, *meshComponentClass = nullptr;

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

		mono_add_internal_call("VoidEngine.Scene.ComponentUpdater::Finalize", (void*) ComponentUpdater_finalize);
		mono_add_internal_call("VoidEngine.Scene.ComponentUpdater::GetInstance", (void*) ComponentUpdater_GetInstance);
		mono_add_internal_call("VoidEngine.Scene.ComponentUpdater::GetInstanceCount", (void*) ComponentUpdater_GetInstanceCount);
		mono_add_internal_call("VoidEngine.Scene.ComponentUpdater::IsComponentUpdating", (void*) ComponentUpdater_IsComponentUpdating);
		mono_add_internal_call("VoidEngine.Scene.ComponentUpdater::AddComponent", (void*) ComponentUpdater_AddComponent);
		mono_add_internal_call("VoidEngine.Scene.ComponentUpdater::RemoveComponent", (void*) ComponentUpdater_RemoveComponent);
		mono_add_internal_call("VoidEngine.Scene.ComponentUpdater::HandlesComponent", (void*) ComponentUpdater_HandlesComponent);
		mono_add_internal_call("VoidEngine.Scene.ComponentUpdater::UpdateComponents", (void*) ComponentUpdater_UpdateComponents);

		mono_add_internal_call("VoidEngine.Scene.AObjectComponent::.ctor", (void*) AObjectComponent_ctor);
		mono_add_internal_call("VoidEngine.Scene.AObjectComponent::Finalize", (void*) AObjectComponent_finalize);

		mono_add_internal_call("VoidEngine.Scene.Components.TransformComponent::.ctor", (void*) TransformComponent_ctor);
		mono_add_internal_call("VoidEngine.Scene.Components.TransformComponent::Finalize", (void*) TransformComponent_finalize);
		mono_add_internal_call("VoidEngine.Scene.Components.TransformComponent::set_Position", (void*) TransformComponent_set_Position);
		mono_add_internal_call("VoidEngine.Scene.Components.TransformComponent::get_Position", (void*) TransformComponent_get_Position);
		mono_add_internal_call("VoidEngine.Scene.Components.TransformComponent::set_Rotation", (void*) TransformComponent_set_Rotation);
		mono_add_internal_call("VoidEngine.Scene.Components.TransformComponent::get_Rotation", (void*) TransformComponent_get_Rotation);
		mono_add_internal_call("VoidEngine.Scene.Components.TransformComponent::set_Scale", (void*) TransformComponent_set_Scale);
		mono_add_internal_call("VoidEngine.Scene.Components.TransformComponent::get_Scale", (void*) TransformComponent_get_Scale);
		mono_add_internal_call("VoidEngine.Scene.Components.TransformComponent::GetMatrix", (void*) TransformComponent_GetMatrix);

		mono_add_internal_call("VoidEngine.Scene.Components.MeshComponent::.ctor", (void*) MeshComponent_ctor);
		mono_add_internal_call("VoidEngine.Scene.Components.MeshComponent::Finalize", (void*) MeshComponent_finalize);
		mono_add_internal_call("VoidEngine.Scene.Components.MeshComponent::set_Transform", (void*) MeshComponent_set_Transform);
		mono_add_internal_call("VoidEngine.Scene.Components.MeshComponent::get_Transform", (void*) MeshComponent_get_Transform);
		mono_add_internal_call("VoidEngine.Scene.Components.MeshComponent::set_ToDraw", (void*) MeshComponent_set_Mesh);
		mono_add_internal_call("VoidEngine.Scene.Components.MeshComponent::get_ToDraw", (void*) MeshComponent_get_Mesh);
		mono_add_internal_call("VoidEngine.Scene.Components.MeshComponent::set_Program", (void*) MeshComponent_set_Program);
		mono_add_internal_call("VoidEngine.Scene.Components.MeshComponent::get_Program", (void*) MeshComponent_get_Program);
		mono_add_internal_call("VoidEngine.Scene.Components.MeshComponent::Draw", (void*) MeshComponent_Draw);

		interface = CSharpInterface::getInstance();

		sceneClass = interface->getClass("VoidEngine.Scene", "Scene");
		gameObjectClass = interface->getClass("VoidEngine.Scene", "GameObject");
		componentUpdaterClass = interface->getClass("VoidEngine.Scene", "ComponentUpdater");
		objectComponentClass = interface->getClass("VoidEngine.Scene", "AObjectComponent");
		transformComponentClass = interface->getClass("VoidEngine.Scene.Components", "TransformComponent");
		meshComponentClass = interface->getClass("VoidEngine.Scene.Components", "MeshComponent");
	}

	MonoClass *getSceneClass(void) { return sceneClass; }
	MonoClass *getGameObjectClass(void) { return gameObjectClass; }
	MonoClass *getComponentUpdaterClass(void) { return componentUpdaterClass; }
	MonoClass *getAObjectComponentClass(void) { return objectComponentClass; }
	MonoClass *getTransformComponentClass(void) { return transformComponentClass; }
	MonoClass *getMeshComponentClass(void) { return meshComponentClass; }

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

	void ComponentUpdater_finalize(MonoObject *self) {
		if(self == nullptr) {
			mono_raise_exception(mono_get_exception_null_reference());
			return;
		}

		MonoClassField *cxxObject = mono_class_get_field_from_name(getComponentUpdaterClass(), "cxxObject");
		shared_ptr<ComponentUpdater> *updater = nullptr;
		mono_field_get_value(self, cxxObject, updater);
		if(updater == nullptr) delete updater;
	}

	MonoObject *ComponentUpdater_GetInstance(uint32_t idx) {
		shared_ptr<ComponentUpdater> *updater = new shared_ptr<ComponentUpdater>(ComponentUpdater::getInstance(idx));

		MonoObject *obj = interface->allocClass(getComponentUpdaterClass());
		MonoClassField *cxxObject = mono_class_get_field_from_name(getComponentUpdaterClass(), "cxxObject");
		mono_field_set_value(obj, cxxObject, &updater);

		return obj;
	}

	uint32_t ComponentUpdater_GetInstanceCount() {
		return ComponentUpdater::getInstanceCount();
	}

	bool ComponentUpdater_IsComponentUpdating(MonoObject *component) {
		if(component == nullptr) {
			mono_raise_exception(mono_get_exception_null_reference());
			return false;
		}

		MonoClassField *cxxObject = mono_class_get_field_from_name(getAObjectComponentClass(), "cxxObject");
		shared_ptr<VoidEngine::Scene::AObjectComponent> *comp = nullptr;
		mono_field_get_value(component, cxxObject, &comp);
		
		return ComponentUpdater::isComponentUpdating(*comp);
	}

	void ComponentUpdater_AddComponent(MonoObject *self, MonoObject *component) {
		if(self == nullptr || component == nullptr) {
			mono_raise_exception(mono_get_exception_null_reference());
			return;
		}

		shared_ptr<ComponentUpdater> *updater = nullptr;
		MonoClassField *cxxObject = mono_class_get_field_from_name(getComponentUpdaterClass(), "cxxObject");
		mono_field_get_value(self, cxxObject, &updater);

		shared_ptr<VoidEngine::Scene::AObjectComponent> *comp = nullptr;
		MonoClassField *compCxxObject = mono_class_get_field_from_name(getAObjectComponentClass(), "cxxObject");
		mono_field_get_value(component, compCxxObject, &comp);

		(*updater)->addComponent(*comp);
	}

	void ComponentUpdater_RemoveComponent(MonoObject *self, MonoObject *component) {
		if(self == nullptr || component == nullptr) {
			mono_raise_exception(mono_get_exception_null_reference());
			return;
		}

		shared_ptr<ComponentUpdater> *updater = nullptr;
		MonoClassField *cxxObject = mono_class_get_field_from_name(getComponentUpdaterClass(), "cxxObject");
		mono_field_get_value(self, cxxObject, &updater);

		shared_ptr<VoidEngine::Scene::AObjectComponent> *comp = nullptr;
		MonoClassField *compCxxObject = mono_class_get_field_from_name(getAObjectComponentClass(), "cxxObject");
		mono_field_get_value(component, compCxxObject, &comp);

		(*updater)->removeComponent(*comp);
	}

	bool ComponentUpdater_HandlesComponent(MonoObject *self, MonoObject *component) {
		if(self == nullptr || component == nullptr) {
			mono_raise_exception(mono_get_exception_null_reference());
			return false;
		}

		shared_ptr<ComponentUpdater> *updater = nullptr;
		MonoClassField *cxxObject = mono_class_get_field_from_name(getComponentUpdaterClass(), "cxxObject");
		mono_field_get_value(self, cxxObject, &updater);

		shared_ptr<VoidEngine::Scene::AObjectComponent> *comp = nullptr;
		MonoClassField *compCxxObject = mono_class_get_field_from_name(getAObjectComponentClass(), "cxxObject");
		mono_field_get_value(component, compCxxObject, &comp);

		return (*updater)->handlesComponent(*comp);
	}

	void ComponentUpdater_UpdateComponents(MonoObject *self, double delta) {
		if(self == nullptr) {
			mono_raise_exception(mono_get_exception_null_reference());
			return;
		}

		shared_ptr<ComponentUpdater> *updater = nullptr;
		MonoClassField *cxxObject = mono_class_get_field_from_name(getComponentUpdaterClass(), "cxxObject");
		mono_field_get_value(self, cxxObject, &updater);

		(*updater)->updateComponents(delta);
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
		shared_ptr<TransformComponent> *comp = new shared_ptr<TransformComponent>(new TransformComponent);
		mono_field_set_value(self, cxxObject, &comp);
	}

	void TransformComponent_finalize(MonoObject *self) {
		if(self == nullptr) {
			mono_raise_exception(mono_get_exception_null_reference());
			return;
		}

		MonoClassField *cxxObject = mono_class_get_field_from_name(getAObjectComponentClass(), "cxxObject");
		shared_ptr<TransformComponent> *comp = nullptr;
		mono_field_get_value(self, cxxObject, &comp);
		if(comp != nullptr) delete comp;
	}

	void TransformComponent_set_Position(MonoObject *self, glm::vec3 position) {
		if(self == nullptr) {
			mono_raise_exception(mono_get_exception_null_reference());
			return;
		}

		MonoClassField *cxxObject = mono_class_get_field_from_name(getTransformComponentClass(), "cxxObject");
		shared_ptr<TransformComponent> *comp = nullptr;
		mono_field_get_value(self, cxxObject, &comp);

		(*comp)->position = position;
	}

	glm::vec3 TransformComponent_get_Position(MonoObject *self) {
		if(self == nullptr) {
			mono_raise_exception(mono_get_exception_null_reference());
			return { 0.0f, 0.0f, 0.0f };
		}

		MonoClassField *cxxObject = mono_class_get_field_from_name(getTransformComponentClass(), "cxxObject");
		shared_ptr<TransformComponent> *comp = nullptr;
		mono_field_get_value(self, cxxObject, &comp);

		return (*comp)->position;
	}

	void TransformComponent_set_Rotation(MonoObject *self, glm::vec3 rotation) {
		if(self == nullptr) {
			mono_raise_exception(mono_get_exception_null_reference());
			return;
		}

		MonoClassField *cxxObject = mono_class_get_field_from_name(getTransformComponentClass(), "cxxObject");
		shared_ptr<TransformComponent> *comp = nullptr;
		mono_field_get_value(self, cxxObject, &comp);

		(*comp)->rotation = rotation;
	}

	glm::vec3 TransformComponent_get_Rotation(MonoObject *self) {
		if(self == nullptr) {
			mono_raise_exception(mono_get_exception_null_reference());
			return { 0.0f, 0.0f, 0.0f };
		}

		MonoClassField *cxxObject = mono_class_get_field_from_name(getTransformComponentClass(), "cxxObject");
		shared_ptr<TransformComponent> *comp = nullptr;
		mono_field_get_value(self, cxxObject, &comp);

		return (*comp)->rotation;
	}

	void TransformComponent_set_Scale(MonoObject *self, glm::vec3 scale) {
		if(self == nullptr) {
			mono_raise_exception(mono_get_exception_null_reference());
			return;
		}

		MonoClassField *cxxObject = mono_class_get_field_from_name(getTransformComponentClass(), "cxxObject");
		shared_ptr<TransformComponent> *comp = nullptr;
		mono_field_get_value(self, cxxObject, &comp);

		(*comp)->scale = scale;
	}

	glm::vec3 TransformComponent_get_Scale(MonoObject *self) {
		if(self == nullptr) {
			mono_raise_exception(mono_get_exception_null_reference());
			return { 1.0f, 1.0f, 1.0f };
		}

		MonoClassField *cxxObject = mono_class_get_field_from_name(getTransformComponentClass(), "cxxObject");
		shared_ptr<TransformComponent> *comp = nullptr;
		mono_field_get_value(self, cxxObject, &comp);

		return (*comp)->scale;
	}

	glm::mat4 TransformComponent_GetMatrix(MonoObject *self) {
		if(self == nullptr) {
			mono_raise_exception(mono_get_exception_null_reference());
			return glm::mat4(1.0f);
		}

		MonoClassField *cxxObject = mono_class_get_field_from_name(getAObjectComponentClass(), "cxxObject");
		shared_ptr<TransformComponent> *comp = nullptr;
		mono_field_get_value(self, cxxObject, &comp);

		return (*comp)->getMatrix();
	}

	void MeshComponent_ctor(MonoObject *self) {
		if(self == nullptr) {
			mono_raise_exception(mono_get_exception_null_reference());
			return;
		}

		MonoClassField *cxxObject = mono_class_get_field_from_name(getMeshComponentClass(), "cxxObject");
		shared_ptr<MeshComponent> *comp = new shared_ptr<MeshComponent>(new MeshComponent);
		mono_field_set_value(self, cxxObject, &comp);
	}

	void MeshComponent_finalize(MonoObject *self) {
		if(self == nullptr) {
			mono_raise_exception(mono_get_exception_null_reference());
			return;
		}

		MonoClassField *cxxObject = mono_class_get_field_from_name(getMeshComponentClass(), "cxxObject");
		shared_ptr<MeshComponent> *comp = nullptr;
		mono_field_get_value(self, cxxObject, &comp);
		if(comp != nullptr) delete comp;
	}

	void MeshComponent_set_Transform(MonoObject *self, MonoObject *transform) {
		if(self == nullptr) {
			mono_raise_exception(mono_get_exception_null_reference());
			return;
		}

		MonoClassField *cxxObject = mono_class_get_field_from_name(getMeshComponentClass(), "cxxObject");
		shared_ptr<MeshComponent> *comp = nullptr;
		mono_field_get_value(self, cxxObject, &comp);

		if(transform == nullptr) {
			(*comp)->setTransform(nullptr);
			return;
		}

		MonoClassField *transformCxxObject = mono_class_get_field_from_name(getTransformComponentClass(), "cxxObject");
		shared_ptr<TransformComponent> *trnsComp = nullptr;
		mono_field_get_value(transform, transformCxxObject, &trnsComp);

		(*comp)->setTransform(shared_ptr<TransformComponent>(*trnsComp));
	}

	MonoObject *MeshComponent_get_Transform(MonoObject *self) {
		if(self == nullptr) {
			mono_raise_exception(mono_get_exception_null_reference());
			return nullptr;
		}

		MonoClassField *cxxObject = mono_class_get_field_from_name(getMeshComponentClass(), "cxxObject");
		shared_ptr<MeshComponent> *comp = nullptr;
		mono_field_get_value(self, cxxObject, &comp);

		shared_ptr<TransformComponent> trns = (*comp)->getTransform();
		if(trns == nullptr) return nullptr;

		MonoObject *trnsObj = interface->allocClass(getTransformComponentClass());
		MonoClassField *trnsCxxObject = mono_class_get_field_from_name(getTransformComponentClass(), "cxxObject");
		shared_ptr<TransformComponent> *trnsPtr = new shared_ptr<TransformComponent>(trns);
		mono_field_set_value(trnsObj, trnsCxxObject, &trnsPtr);

		return trnsObj;
	}

	void MeshComponent_set_Mesh(MonoObject *self, MonoObject *mesh) {
		if(self == nullptr) {
			mono_raise_exception(mono_get_exception_null_reference());
			return;
		}

		MonoClassField *cxxObject = mono_class_get_field_from_name(getMeshComponentClass(), "cxxObject");
		shared_ptr<MeshComponent> *comp = nullptr;
		mono_field_get_value(self, cxxObject, &comp);

		if(mesh == nullptr) {
			(*comp)->setMesh(nullptr);
			return;
		}

		MonoClassField *meshCxxObject = mono_class_get_field_from_name(IO::GFX::getMeshClass(), "cxxObject");
		shared_ptr<VoidEngine::IO::GFX::Mesh> *gfxMesh = nullptr;
		mono_field_get_value(mesh, meshCxxObject, &gfxMesh);

		(*comp)->setMesh(shared_ptr<VoidEngine::IO::GFX::Mesh>(*gfxMesh));
	}

	MonoObject *MeshComponent_get_Mesh(MonoObject *self) {
		if(self == nullptr) {
			mono_raise_exception(mono_get_exception_null_reference());
			return nullptr;
		}

		MonoClassField *cxxObject = mono_class_get_field_from_name(getMeshComponentClass(), "cxxObject");
		shared_ptr<MeshComponent> *comp = nullptr;
		mono_field_get_value(self, cxxObject, &comp);

		shared_ptr<VoidEngine::IO::GFX::Mesh> mesh = (*comp)->getMesh();
		if(mesh == nullptr) return nullptr;

		shared_ptr<VoidEngine::IO::GFX::Mesh> *meshPtr = new shared_ptr<VoidEngine::IO::GFX::Mesh>(mesh);
		MonoObject *meshObj = interface->allocClass(IO::GFX::getMeshClass());
		MonoClassField *meshCxxObject = mono_class_get_field_from_name(IO::GFX::getMeshClass(), "cxxObject");
		mono_field_set_value(meshObj, meshCxxObject, &meshPtr);
		return meshObj;
	}

	void MeshComponent_set_Program(MonoObject *self, MonoObject *program) {
		if(self == nullptr) {
			mono_raise_exception(mono_get_exception_null_reference());
			return;
		}

		MonoClassField *cxxObject = mono_class_get_field_from_name(getMeshComponentClass(), "cxxObject");
		shared_ptr<MeshComponent> *comp = nullptr;
		mono_field_get_value(self, cxxObject, &comp);

		if(program == nullptr) {
			(*comp)->setProgram(nullptr);
			return;
		}

		MonoClassField *programCxxObject = mono_class_get_field_from_name(IO::GFX::getGraphicsProgramClass(), "cxxObject");
		shared_ptr<VoidEngine::IO::GFX::GraphicsProgram> *gfxProgram = nullptr;
		mono_field_get_value(program, programCxxObject, &gfxProgram);
		(*comp)->setProgram(shared_ptr<VoidEngine::IO::GFX::GraphicsProgram>(*gfxProgram));
	}

	MonoObject *MeshComponent_get_Program(MonoObject *self) {
		if(self == nullptr) {
			mono_raise_exception(mono_get_exception_null_reference());
			return nullptr;
		}

		MonoClassField *cxxObject = mono_class_get_field_from_name(getMeshComponentClass(), "cxxObject");
		shared_ptr<MeshComponent> *comp = nullptr;
		mono_field_get_value(self, cxxObject, &comp);

		shared_ptr<VoidEngine::IO::GFX::GraphicsProgram> program = (*comp)->getProgram();
		if(program == nullptr) return nullptr;

		MonoClassField *programCxxObject = mono_class_get_field_from_name(IO::GFX::getGraphicsProgramClass(), "cxxObject");
		shared_ptr<VoidEngine::IO::GFX::GraphicsProgram> *gfxProgram = new shared_ptr<VoidEngine::IO::GFX::GraphicsProgram>(program);
		MonoObject *programObj = interface->allocClass(IO::GFX::getGraphicsProgramClass());
		mono_field_set_value(programObj, programCxxObject, &gfxProgram);
		return programObj;
	}

	void MeshComponent_Draw(MonoObject *self, double delta) {
		if(self == nullptr) {
			mono_raise_exception(mono_get_exception_null_reference());
			return;
		}

		MonoClassField *cxxObject = mono_class_get_field_from_name(getMeshComponentClass(), "cxxObject");
		shared_ptr<MeshComponent> *comp = nullptr;
		mono_field_get_value(self, cxxObject, &comp);

		(*comp)->draw(delta);
	}
}

