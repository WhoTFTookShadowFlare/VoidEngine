#include "ve/io/gfx/mesh.hpp"
#include "ve/io/res_providers/mesh/a_provider.hpp"

namespace VoidEngine::IO::GFX {
	void Mesh::setMeshProvider(std::shared_ptr<VoidEngine::IO::ResourceProviders::AMeshProvider> provider) {
		if(this->provider != nullptr) {
			this->provider->meshChanged -= weak_from_this();
		}

		this->provider = provider;
		buildMesh();

		if(this->provider != nullptr) {
			this->provider->meshChanged += weak_from_this();
		}
	}

	std::shared_ptr<VoidEngine::IO::ResourceProviders::AMeshProvider> Mesh::getMeshProvider() {
		return provider;
	}

	void Mesh::onEvent(VoidEngine::IO::ResourceProviders::EMeshProviderChanged& evt) {
		buildMesh();
	}
}
