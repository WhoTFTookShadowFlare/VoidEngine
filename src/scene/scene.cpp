#include "ve/scene/scene.hpp"
#include "ve/io/gfx/render_frame.hpp"
#include "ve/io/gfx/render_target.hpp"
#include "ve/io/gfx/renderer.hpp"
#include "ve/io/res_providers/model/file_provider.hpp"
#include "ve/class_db.hpp"
#include "ve/scene/component_updater.hpp"
#include "ve/scene/events.hpp"
#include "ve/scene/game_object.hpp"
#include "ve/scene/components/camera.hpp"
#include "ve/io/res_providers/model/a_provider.hpp"
#include "ve/variant.hpp"
#include <toml++/impl/forward_declarations.hpp>
#include <toml++/impl/key.hpp>
#include <toml++/toml.hpp>
#include <algorithm>
#include <filesystem>
#include <map>
#include <memory>
#include <print>
#include <string>
#include <vector>

namespace VoidEngine::Scene {
	const Class Scene::ClassData = {
		.name = "Scene"
	};

	std::shared_ptr<Scene> Scene::create() {
		return std::shared_ptr<Scene>(new Scene);
	}

	std::shared_ptr<Scene> Scene::loadFrom(std::filesystem::path path) {
		if(!std::filesystem::exists(path)) {
			std::println("[ERR] Could not load scene {}, path does not exist", path.string());
			return nullptr;
		}

		if(!std::filesystem::is_directory(path)) {
			path = path.parent_path();
		}

		if(!(std::filesystem::exists(path / "root.toml") && !std::filesystem::is_directory(path / "root.toml"))) {
			std::println("[ERR] Could not find {}/root.toml", path.string());
			return nullptr;
		}

		auto compDB = ClassDB::getInstance();
		auto compUpdater = ComponentUpdater::getInstance();

		auto deserializedScene = Scene::create();

		std::ifstream simple_root_toml = std::ifstream(path / "root.toml");
		toml::table tbl = toml::parse(simple_root_toml);
		toml::array* loadOrder = tbl["scene"]["loadOrder"].as_array();
		simple_root_toml.close();

		std::unordered_map<std::string, std::vector<std::shared_ptr<VoidEngine::Scene::AObjectComponent>>> components;

		std::unordered_map<std::string, std::vector<std::shared_ptr<VoidEngine::Scene::GameObject>>> objects;
		std::unordered_map<std::shared_ptr<VoidEngine::Scene::GameObject>, std::vector<std::string>> objComponentRefs;

		std::unordered_map<std::string, std::vector<std::shared_ptr<VoidEngine::IO::ResourceProviders::AModelProvider>>> models;

		for(size_t idx = 0; idx < loadOrder->size(); idx++) {
			std::filesystem::path targetFilePath = path / loadOrder->get(idx)->as_string()->get();
			std::ifstream chunk_file = std::ifstream(targetFilePath);
			toml::table chunk = toml::parse(chunk_file);

			if(chunk.contains("component") && chunk["component"].is_array()) {
				toml::array* chunk_components = chunk["component"].as_array();
				if(chunk_components->size() > 0) {
					std::vector<std::shared_ptr<VoidEngine::Scene::AObjectComponent>> comps;

					for(size_t idx = 0; idx < chunk_components->size(); idx++) {
						std::string clsName = chunk_components->get(idx)->as_table()->get("type")->as_string()->get();
						const VoidEngine::Class* cls = compDB->getClassByName(clsName);
						if(cls == nullptr) {
							std::println("[ERR] Could not find class {}", clsName);
							continue;
						}
						if(!cls->instanceOf(&AObjectComponent::ClassData)) {
							std::println("[ERR] Class \"{}\" is not of type AObjectComponent", clsName);
							continue;
						}
						if(cls->isAbstract()) {
							std::println("[ERR] Cannot instance abstract class {}", clsName);
							continue;
						}

						auto comp = std::static_pointer_cast<AObjectComponent>(cls->create());
						comps.push_back(comp);
						compUpdater->addComponent(comp);
					}

					components[targetFilePath.filename().replace_extension("").string()] = comps;
				}
			}

			if(chunk.contains("object") && chunk["object"].is_array()) {
				toml::array* objectsArr = chunk["object"].as_array();
				for(size_t idx = 0; idx < objectsArr->size(); idx++) {
					toml::table* objTable = objectsArr->get(idx)->as_table();
					
					if(!(objTable->contains("name") && objTable->get("name")->is_string())) {
						std::println("Object is missing required field name");
						continue;
					}

					std::string name = objTable->get("name")->as_string()->get();
					std::shared_ptr<VoidEngine::Scene::GameObject> obj = VoidEngine::Scene::GameObject::create(name);
					std::string parent = (objTable->contains("parent") ? objTable->get("parent")->as_string()->get() : "");
					if(!objects.contains(parent)) objects[parent] = std::vector<std::shared_ptr<VoidEngine::Scene::GameObject>>();
					objects[parent].push_back(obj);

					if(objTable->contains("components") && objTable->get("components")->is_array()) {
						toml::array* componentArray = objTable->get("components")->as_array();
						std::vector<std::string> compRefs;
						for(size_t idx = 0; idx < componentArray->size(); idx++) {
							toml::node* entry = componentArray->get(idx);
							if(entry->is_string()) {
								compRefs.push_back(entry->as_string()->get());
							} else if(entry->is_table()) {
								std::string clsName = entry->as_table()->get("type")->as_string()->get();
								const VoidEngine::Class* cls = compDB->getClassByName(clsName);
								if(cls == nullptr) {
									std::println("[ERR] Could not find class {}", clsName);
									continue;
								}
								if(!cls->instanceOf(&AObjectComponent::ClassData)) {
									std::println("[ERR] Class \"{}\" is not of type AObjectComponent", clsName);
									continue;
								}

								auto comp = std::static_pointer_cast<AObjectComponent>(cls->create());
								compUpdater->addComponent(comp);
								obj->addComponent(comp);
							} else {
								std::println("[WARN] components must be a table (inline component) or string (component reference), skipping");
							}
						}
						objComponentRefs[obj] = compRefs;
					}

					std::for_each(
						GameObject::ClassData.properties.cbegin(), GameObject::ClassData.properties.cend(),
						[&obj, objTable](const auto prop) {
							if(prop->isReadOnly()) return;
							if(!objTable->contains(prop->name)) return;
							toml::node* node = objTable->get(prop->name);
							if(!node->is_array()) return;

							toml::array* arr = node->as_array();
							if(arr->size() < 3) return;
							Variant value = glm::vec3 {
								(arr->get(0)->is_floating_point() ? arr->get(0)->as_floating_point()->get() : arr->get(0)->as_integer()->get()),
								(arr->get(1)->is_floating_point() ? arr->get(1)->as_floating_point()->get() : arr->get(1)->as_integer()->get()),
								(arr->get(2)->is_floating_point() ? arr->get(2)->as_floating_point()->get() : arr->get(2)->as_integer()->get())
							};
							prop->set(obj, value);
						}
					);
				}
			}

			if(chunk.contains("model") && chunk["model"].is_array()) {
				toml::array* model = chunk["model"].as_array(); // TODO: Load models and add them to the objects list
				for(size_t idx = 0; idx < model->size(); idx++) {
					toml::table* modelData = model->get(idx)->as_table();
					if(!(modelData->contains("parent") && modelData->contains("provider"))) {
						std::println("[ERR] [[model]] is missing a required key");
						continue;
					}

					if(!(modelData->get("parent")->is_string() && modelData->get("provider")->is_table())) {
						std::println("[ERR] [[model]] is missing a required key is not the correct type (parent is string, providier is table)");
						continue;
					}

					std::string parent = modelData->get("parent")->as_string()->get();
					toml::table* providerData = modelData->get("provider")->as_table();

					if(!(providerData->contains("type") && providerData->get("type")->is_string())) {
						std::println("[ERR] [[model]] provider type is missing");
						continue;
					}

					std::string providerType = providerData->get("type")->as_string()->get();
					if(providerType != "FileModelProvider") {
						std::println("[WARN] Only FileModelProvider is currently supported, skipping");
						continue;
					}

					if(!(providerData->contains("path") && providerData->get("path")->is_string())) {
						std::println("provider of type FileModelProvider is missing required field path");
						continue;
					}

					std::filesystem::path path = providerData->get("path")->as_string()->get();
					
					std::vector<std::shared_ptr<VoidEngine::IO::ResourceProviders::AModelProvider>>& objModels = models[parent];
					objModels.push_back(
						std::shared_ptr<VoidEngine::IO::ResourceProviders::FileModelProvider>(
							new VoidEngine::IO::ResourceProviders::FileModelProvider(path)
						)
					);
				}
			}

			chunk_file.close();
		}

		if(!objects.contains("")) {
			std::println("[FATAL] Scene does not have any root objects");
			return nullptr;
		}

		auto& rootObjects = objects[""];
		std::for_each(rootObjects.begin(), rootObjects.end(), [&deserializedScene](auto& obj) {
			deserializedScene->addObject(obj);
		});
		objects.erase("");

		{
			size_t rem = objects.size();
			size_t remPrev = rem;
			do {
				remPrev = rem;

				std::vector<std::string> forRemoval;
				std::for_each(objects.begin(), objects.end(), [&](auto& entry) {
					std::shared_ptr<VoidEngine::Scene::GameObject> obj = deserializedScene->getObjectFromPath(entry.first);
					if(obj == nullptr) return;
					forRemoval.push_back(entry.first);
					std::for_each(entry.second.begin(), entry.second.end(), [&](auto& child) {
						obj->addChild(child);
					});
				});

				std::for_each(forRemoval.cbegin(), forRemoval.cend(), [&objects](const auto& removal) {
					objects.erase(removal);
				});

				rem = objects.size();
			} while(rem != remPrev);

			if(rem > 0) {
				std::println("[WARN] Orphan objects detected while building the scene, killing children");
			}
		}

		std::for_each(objComponentRefs.begin(), objComponentRefs.end(), [&](const auto& entry) {
			std::shared_ptr<VoidEngine::Scene::GameObject> object = entry.first;
			std::for_each(entry.second.cbegin(), entry.second.cend(), [&object, &components](const auto& compRef) {
				size_t splitPos = compRef.find_last_of('.');
				if(splitPos == std::string::npos) {
					std::println("[ERR] Invalid component reference \"{}\"", compRef);
					return;
				}

				std::string targetFile = compRef.substr(0, splitPos);
				std::string targetIdx = compRef.substr(splitPos + 1);
				int idx = 0;
				try {
					idx = std::stoi(targetIdx);
				} catch(std::invalid_argument& ex) {
					std::println("{}", ex.what());
					return;
				} catch(std::out_of_range& ex) {
					std::println("{}", ex.what());
					return;
				}

				object->addComponent(components[targetFile][idx]);
			});
		});
		
		std::for_each(models.begin(), models.end(), [&](auto& entry) {
			auto obj = deserializedScene->getObjectFromPath(entry.first);
			if(obj == nullptr) {
				std::println("[ERR] Could not find {} to add model to", entry.first);
				return;
			}

			std::for_each(entry.second.begin(), entry.second.end(), [&obj](auto& model) {
				obj->addChild(model->generateGameObject());
			});
		});

		if(tbl["scene"].as_table()->contains("startingCamera") && tbl["scene"]["startingCamera"].is_string()) {
			deserializedScene->setCamera(deserializedScene->getObjectFromPath(tbl["scene"]["startingCamera"].as_string()->get()));
		}

		return deserializedScene;
	}

	std::shared_ptr<GameObject> Scene::getObject(std::string name) {
		return objects[name];
	}

	void Scene::addObject(std::shared_ptr<GameObject> obj) {
		auto prev = getObject(obj->getName());
		if(prev != nullptr) {
			Events::ERemovedFromScene evt(shared_from_this(), prev);
			prev->onRemovedFromScene(evt);
		}

		objects[obj->getName()] = obj;

		if(obj != nullptr) {
			Events::EAddedToScene evt(shared_from_this(), obj);
			obj->onAddedToScene(evt);
		}
	}

	std::shared_ptr<GameObject> Scene::getObjectFromPath(std::string path) {
		size_t split = path.find_first_of('/');
		if(split == std::string::npos) {
			return getObject(path);
		}

		std::string next = path.substr(0, split), remaining = path.substr(split + 1);

		std::shared_ptr<GameObject> child = getObject(next);
		if(child == nullptr) return nullptr;
		return child->getChildFromPath(remaining);
	}


	std::vector<std::shared_ptr<GameObject>> Scene::getObjects() {
		std::vector<std::shared_ptr<GameObject>> objVec;

		for(auto obj = objects.begin(); obj != objects.end(); obj++) {
			objVec.push_back(obj->second);
		}

		return objVec;
	}

	void Scene::setCamera(std::shared_ptr<GameObject> obj) {
		if(obj == nullptr) {
			currentCamera = nullptr;
			return;
		}

		std::shared_ptr<AObjectComponent> camera = obj->getFirstOfType(&Components::ACamera::ClassData);
		if(camera == nullptr) return;
		currentCamera = obj;
	}

	std::shared_ptr<GameObject> Scene::getCamera() {
		return currentCamera;
	}

	IO::GFX::DirectionalLight Scene::getDirectionalLight() {
		return light;
	}

	void Scene::setDirectionalLight(IO::GFX::DirectionalLight value) {
		light = value;
	}

	std::shared_ptr<IO::GFX::RenderFrame> Scene::draw(double delta, std::shared_ptr<IO::GFX::IRenderTarget> target) {
		auto frame = IO::GFX::RenderFrame::create();
		frame->setTarget(target);
		frame->setDirectionalLight(light);
		auto renderer = IO::GFX::Renderer::getInstance();
		// renderer->bindRenderTarget(target);
		// renderer->useDepth(true);
		if(currentCamera != nullptr) {
			auto camComp = std::static_pointer_cast<Components::ACamera>(currentCamera->getFirstOfType(&Components::ACamera::ClassData));
			frame->setView(camComp->getView(currentCamera));
			frame->setProjection(camComp->getProjection(target));
		}
		Events::ESceneDraw draw(delta, frame, shared_from_this());
		std::for_each(objects.begin(), objects.end(), [&draw](auto& obj) {
			obj.second->draw(draw);
		});
		// renderer->bindRenderTarget(target);
		// IO::GFX::Renderer::getInstance()->useDepth(false);

		return frame;
	}
}
