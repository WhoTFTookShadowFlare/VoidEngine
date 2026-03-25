#include "ve/io/gfx/mesh.hpp"
#include "ve/io/gfx/mesh_provider.hpp"

namespace VoidEngine::IO::GFX {
	void Mesh::setMeshProvider(std::shared_ptr<AMeshProvider> provider) {
		if(this->provider != nullptr) {
			this->provider->meshChanged -= weak_from_this();
		}

		this->provider = provider;
		buildMesh();

		if(this->provider != nullptr) {
			this->provider->meshChanged += weak_from_this();
		}
	}

	std::shared_ptr<AMeshProvider> Mesh::getMeshProvider() {
		return provider;
	}

	void Mesh::onEvent(EMeshProviderChanged& evt) {
		buildMesh();
	}
}
