#pragma once

#include "ve/io/gfx/mesh.hpp"
#include "ve/io/gfx/program_uniform.hpp"
#include "ve/scene/component_db.hpp"
#include "ve/scene/object_component.hpp"
#include <memory>
#include <optional>

namespace VoidEngine::Scene::Components {
	class MeshComponent : public AObjectComponent,
		public Event::IEventListener<Events::EComponentDraw>
	{
		std::shared_ptr<VoidEngine::IO::GFX::Mesh> mesh = nullptr;
		std::shared_ptr<VoidEngine::IO::GFX::GraphicsProgram> program = nullptr;

		std::optional<VoidEngine::IO::GFX::Uniform>
			uProjection = std::nullopt,
			uView = std::nullopt,
			uModel = std::nullopt;

		MeshComponent();
	public:
		static const ComponentClass ClassData;
		static std::shared_ptr<MeshComponent> create();

		void onEvent(Events::EComponentDraw& evt);

		std::shared_ptr<VoidEngine::IO::GFX::Mesh> getMesh();
		std::shared_ptr<VoidEngine::IO::GFX::GraphicsProgram> getProgram();

		void setMesh(std::shared_ptr<VoidEngine::IO::GFX::Mesh> mesh);
		void setProgram(std::shared_ptr<VoidEngine::IO::GFX::GraphicsProgram> program);

		virtual const ComponentClass* getClass() const override { return &ClassData; }
	};
}

