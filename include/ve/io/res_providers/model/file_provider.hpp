#pragma once

#include "ve/io/gfx/mesh.hpp"
#include "ve/io/gfx/renderer.hpp"
#include "ve/io/res_providers/mesh/model_provider.hpp"
#include "ve/io/res_providers/model/a_provider.hpp"
#include "ve/scene/components/mesh.hpp"
#include "ve/scene/game_object.hpp"
#include <assimp/postprocess.h>
#include <assimp/scene.h>
#include <fstream>
#include <filesystem>
#include <memory>
#include <print>

namespace VoidEngine::IO::ResourceProviders {
	class FileModelProvider : public AModelProvider {
	private:
		void processChildren(std::shared_ptr<Scene::GameObject>& object, aiNode* objectNode) {
			for(size_t idx = 0; idx < objectNode->mNumChildren; idx++) {
				std::shared_ptr<Scene::GameObject> child = Scene::GameObject::create(objectNode->mChildren[idx]->mName.C_Str());
				object->addChild(child);
				processChildren(child, objectNode->mChildren[idx]);
			}

			if(objectNode->mNumMeshes > 1)
				std::println("[WARN] More than one mesh on a aiNode, only the first will be used");

			if(objectNode->mNumMeshes > 0) {
				auto meshComp = Scene::Components::MeshComponent::create();
				std::shared_ptr<MeshModelProvider> meshProvider = std::make_shared<MeshModelProvider>(*this, objectNode->mMeshes[0]);
				std::shared_ptr<GFX::Mesh> mesh = GFX::Renderer::getInstance()->createMesh();
				mesh->setMeshProvider(meshProvider);
				meshComp->setMesh(mesh);
				object->addComponent(meshComp);
			}
		}
	public:
		FileModelProvider(std::filesystem::path& path) {
			bool fExists = std::filesystem::exists(path);
			bool isDir = !std::filesystem::is_directory(path);
			bool test = !(fExists && isDir);
			if(test) {
				throw std::runtime_error(std::format("File {} is either a directory or does not exist", path.string()));
			}

			std::ifstream in = std::ifstream(path, std::ios::binary);
			if(!in.is_open()) throw std::runtime_error(std::format("Failed to open file {}", path.string()));
			std::basic_string<uint8_t> raw = std::basic_string<uint8_t>(std::istreambuf_iterator(in), {});
			in.close();

			scene = importer.ReadFileFromMemory(raw.c_str(), raw.length(), aiProcess_Triangulate | aiProcess_JoinIdenticalVertices);
			if(scene == nullptr) throw std::runtime_error(importer.GetErrorString());
		}

		size_t getMeshCount() override { return scene->mNumMeshes; }

		std::shared_ptr<Scene::GameObject> generateGameObject() override {
			std::shared_ptr<Scene::GameObject> object = Scene::GameObject::create(scene->mRootNode->mName.C_Str());

			processChildren(object, scene->mRootNode);

			return object;
		}
		
		~FileModelProvider() {
			importer.FreeScene();
		}
	};
}
