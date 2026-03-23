#pragma once

#include "ve/io/gfx/mesh.hpp"
#include "ve/io/gfx/program_uniform.hpp"
#include "ve/scene/components/transform.hpp"
#include "ve/scene/object_component.hpp"
#include <memory>
#include <optional>

namespace VoidEngine::Scene::Components {
	using namespace std;
	using namespace VoidEngine::IO::GFX;

	class MeshComponent : public AObjectComponent {
		shared_ptr<Mesh> mesh = nullptr;
		shared_ptr<GraphicsProgram> program = nullptr;

		shared_ptr<TransformComponent> transform = nullptr;

		optional<Uniform>
			uProjection = nullopt,
			uView = nullopt,
			uModel = nullopt;
	public:
		void draw(double delta);
		void update(double delta);

		shared_ptr<TransformComponent> getTransform();
		shared_ptr<Mesh> getMesh();
		shared_ptr<GraphicsProgram> getProgram();

		void setTransform(shared_ptr<TransformComponent> transform);
		void setMesh(shared_ptr<Mesh> mesh);
		void setProgram(shared_ptr<GraphicsProgram> program);
	};
}

