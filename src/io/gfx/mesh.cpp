#include "ve/io/gfx/mesh.hpp"
#include "ve/io/gfx/material.hpp"
#include "ve/io/res_providers/mesh/a_provider.hpp"
#include <memory>

namespace VoidEngine::IO::GFX {
	void Mesh::setMeshProvider(std::shared_ptr<VoidEngine::IO::ResourceProviders::AMeshProvider> provider) {
		// FIXME: Event migration
		if(this->provider != nullptr) {
			// this->provider->meshChanged -= weak_from_this();
		}

		this->provider = provider;
		buildMesh();

		if(this->provider != nullptr) {
			// this->provider->meshChanged += weak_from_this();
		}
	}

	std::shared_ptr<VoidEngine::IO::ResourceProviders::AMeshProvider> Mesh::getMeshProvider() {
		return provider;
	}

	void Mesh::setMaterial(std::shared_ptr<Material> value) {
		material = value;
	}

	std::shared_ptr<Material> Mesh::getMaterial() {
		return material;
	}

	void Mesh::onEvent(VoidEngine::IO::ResourceProviders::EMeshProviderChanged& evt) {
		buildMesh();
	}
}
