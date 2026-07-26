#include "ve/io/gfx/mesh.hpp"
#include "ve/scene/components/mesh.hpp"
#include "ve/io/gfx/graphics_program.hpp"
#include "ve/scene/game_object.hpp"
#include <algorithm>
#include <glm/ext/matrix_float4x4.hpp>
#include <memory>

namespace VoidEngine::Scene::Components {
	using namespace std;
	MeshComponent::MeshComponent() {}

	std::shared_ptr<MeshComponent> MeshComponent::create() {
		auto self = std::shared_ptr<MeshComponent>(new MeshComponent);
		self->onDraw += self;
		return self;
	}

	void MeshComponent::onEvent(Events::EComponentDraw& draw) {
		if(program == nullptr) return;
		if(mesh == nullptr) return;

		auto objs = getObjectsUsing();
		std::for_each(objs.cbegin(), objs.cend(), [&](const auto& obj) {
			draw.frame->addDraw(mesh, program, obj->getModelMatrix());
		});
	}

	std::shared_ptr<VoidEngine::IO::GFX::Mesh> MeshComponent::getMesh() {
		return mesh;
	}

	std::shared_ptr<VoidEngine::IO::GFX::GraphicsProgram> MeshComponent::getProgram() {
		return program;
	}

	void MeshComponent::setMesh(std::shared_ptr<VoidEngine::IO::GFX::Mesh> mesh) {
		this->mesh = mesh;
	}

	void MeshComponent::setProgram(std::shared_ptr<VoidEngine::IO::GFX::GraphicsProgram> program) {
		this->program = program;
	}

	const Class MeshComponent::ClassData = {
		.name = "MeshComponent",
	};
}

