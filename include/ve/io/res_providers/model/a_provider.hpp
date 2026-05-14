#pragma once

#include <assimp/Importer.hpp>

namespace VoidEngine::IO::ResourceProviders {
	class AModelProvider {
	private:
	protected:
		Assimp::Importer importer;
		const aiScene *scene;
	public:
		virtual size_t getMeshCount() = 0;

		const aiScene* getScene() { return scene; }
	};
}