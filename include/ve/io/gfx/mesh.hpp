#pragma once

#include "ve/io/res_providers/mesh/a_provider.hpp"
#include "ve/event/event_listener.hpp"
#include "ve/io/gfx/vertex.hpp"
#include <cstdint>
#include <vector>

namespace VoidEngine::IO::GFX {
	class GraphicsProgram;
	class Mesh : public std::enable_shared_from_this<Mesh>,
		public Event::IEventListener<VoidEngine::IO::ResourceProviders::EMeshProviderChanged>
	{
		friend class GraphicsProgram;

		std::shared_ptr<VoidEngine::IO::ResourceProviders::AMeshProvider> provider = nullptr;
		
		virtual void draw() = 0;
	protected:
		virtual void buildMesh() = 0;
	public:
		virtual ~Mesh() {}

		void setMeshProvider(std::shared_ptr<VoidEngine::IO::ResourceProviders::AMeshProvider>);
		std::shared_ptr<VoidEngine::IO::ResourceProviders::AMeshProvider> getMeshProvider();

		void onEvent(VoidEngine::IO::ResourceProviders::EMeshProviderChanged& evt);
	};
}

