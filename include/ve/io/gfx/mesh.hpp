#pragma once

#include "ve/class_db.hpp"
#include "ve/io/gfx/material.hpp"
#include "ve/io/res_providers/mesh/a_provider.hpp"
#include <memory>

namespace VoidEngine::IO::GFX {
	class GraphicsProgram;
	class Mesh : public Object,
		public std::enable_shared_from_this<Mesh>
	{
		friend class GraphicsProgram;

		std::shared_ptr<VoidEngine::IO::ResourceProviders::AMeshProvider> provider = nullptr;
		std::shared_ptr<Material> material = nullptr;
		
		virtual void draw() = 0;
	protected:
		virtual void buildMesh() = 0;
	public:
		static const Class ClassData;
		virtual const Class* getClass() const { return &ClassData; }

		virtual ~Mesh() {}

		void setMeshProvider(std::shared_ptr<VoidEngine::IO::ResourceProviders::AMeshProvider>);
		std::shared_ptr<VoidEngine::IO::ResourceProviders::AMeshProvider> getMeshProvider();

		void setMaterial(std::shared_ptr<Material>);
		std::shared_ptr<Material> getMaterial();

		void onMeshProviderChangedEvent(std::shared_ptr<Object> evt);
	};
}

