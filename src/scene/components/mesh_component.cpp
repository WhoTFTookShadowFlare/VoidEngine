#include "ve/class_event_handler.hpp"
#include "ve/io/gfx/mesh.hpp"
#include "ve/scene/components/mesh.hpp"
#include "ve/io/gfx/graphics_program.hpp"
#include "ve/scene/events.hpp"
#include "ve/scene/game_object.hpp"
#include <algorithm>
#include <glm/ext/matrix_float4x4.hpp>
#include <memory>

namespace VoidEngine::Scene::Components {
	using namespace std;
	MeshComponent::MeshComponent() {}

	std::shared_ptr<MeshComponent> MeshComponent::create() {
		auto self = std::shared_ptr<MeshComponent>(new MeshComponent);
		self->onDraw.addHandler(self);
		return self;
	}

	void MeshComponent::onDrawEvent(std::shared_ptr<Object> evt) {
		if(program == nullptr) return;
		if(mesh == nullptr) return;

		auto draw = std::static_pointer_cast<Events::EComponentDraw>(evt);

		auto objs = getObjectsUsing();
		std::for_each(objs.cbegin(), objs.cend(), [&](const std::shared_ptr<GameObject>& obj) {
			draw->frame->addDraw(mesh, program, obj->getModelMatrix());
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
		.eventHandlers = {
			new NativeEventHandler(&Events::EComponentDraw::ClassData, &MeshComponent::onDrawEvent)
		},
		.constructor = new NativeConstructor(MeshComponent::create),
	};
}

