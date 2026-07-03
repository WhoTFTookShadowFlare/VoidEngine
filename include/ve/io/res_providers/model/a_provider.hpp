#pragma once

#include "ve/scene/game_object.hpp"
#include <assimp/Importer.hpp>
#include <memory>

namespace VoidEngine::IO::ResourceProviders {
	class AModelProvider {
	private:
	protected:
		Assimp::Importer importer;
		const aiScene *scene;
	public:
		virtual size_t getMeshCount() = 0;
		virtual std::shared_ptr<Scene::GameObject> generateGameObject() = 0;

		const aiScene* getScene() { return scene; }
	};
}