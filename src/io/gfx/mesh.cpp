#include "ve/io/gfx/mesh.hpp"
#include "ve/class_event_handler.hpp"
#include "ve/io/gfx/material.hpp"
#include "ve/io/res_providers/mesh/a_provider.hpp"
#include "ve/object.hpp"
#include <memory>

namespace VoidEngine::IO::GFX {
	const Class Mesh::ClassData = {
		.name = "Mesh",
		.eventHandlers = {
			new NativeEventHandler(&ResourceProviders::EMeshProviderChanged::ClassData, &Mesh::onMeshProviderChangedEvent)
		}
	};
	
	void Mesh::setMeshProvider(std::shared_ptr<VoidEngine::IO::ResourceProviders::AMeshProvider> provider) {
		if(this->provider != nullptr) {
			this->provider->meshChanged.addHandler(shared_from_this());
		}

		this->provider = provider;
		buildMesh();

		if(this->provider != nullptr) {
			this->provider->meshChanged.addHandler(shared_from_this());
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

	void Mesh::onMeshProviderChangedEvent(std::shared_ptr<Object> evt) {
		buildMesh();
	}
}
