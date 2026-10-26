#include <ve/scene/components/gfx/mesh_component.hpp>

#include <ve/scene/scene.hpp>
#include <ve/scene/game_object.hpp>
#include <ve/class_event_handler.hpp>
#include <ve/scene/events.hpp>

#include <ve/io/gfx/graphics_program.hpp>

namespace VoidEngine::Scene::Components::GFX {
	const ::VoidEngine::Class MeshComponentDrawCall::ClassData = {
		.name = "MeshComponentDrawCall",
		.super = &IO::GFX::AFrameDrawCall::ClassData,
		.constructor = new NativeConstructor(&MeshComponentDrawCall::create),
		.flags = ClassFlags::FINAL
	};

	std::shared_ptr<MeshComponentDrawCall> MeshComponentDrawCall::create() {
		return std::shared_ptr<MeshComponentDrawCall>(new MeshComponentDrawCall);
	}
	
	void MeshComponentDrawCall::draw() {
		if(getMesh() == nullptr || getProgram() == nullptr) return;
		auto program = getProgram();

		std::optional<IO::GFX::Uniform> uModel = program->queryUniform("uModel");
		if(uModel.has_value()) {
			program->setUniform(uModel.value(), getModelMatrix());
		}
		
		program->draw(getMesh());
	}

	std::shared_ptr<IO::GFX::Mesh> MeshComponentDrawCall::getMesh() const {
		return mesh;
	}

	void MeshComponentDrawCall::setMesh(std::shared_ptr<IO::GFX::Mesh> value) {
		mesh = value;
	}
	
	glm::mat4 MeshComponentDrawCall::getModelMatrix() const {
		return modelMatrix;
	}

	void MeshComponentDrawCall::setModelMatrix(glm::mat4 value) {
		modelMatrix = value;
	}

	const ::VoidEngine::Class MeshComponent::ClassData = {
		.name = "MeshComponent",
		.super = &AMonoObjectComponent::ClassData,
		.eventHandlers = {
			new NativeEventHandler(&EComponentAdded::ClassData, &MeshComponent::handleAddedToObject),
			new NativeEventHandler(&EComponentRemoved::ClassData, &MeshComponent::handleRemovedFromObject),
			new NativeEventHandler(&EAddedToScene::ClassData, &MeshComponent::handleAddedToScene),
			new NativeEventHandler(&ERemovedFromScene::ClassData, &MeshComponent::handleRemovedFromScene),
			new NativeEventHandler(&EDraw::ClassData, &MeshComponent::handleDraw)
		},
		.constructor = new NativeConstructor(&MeshComponent::create),
		.flags = ClassFlags::FINAL
	};

	std::shared_ptr<MeshComponent> MeshComponent::create() {
		auto self = std::shared_ptr<MeshComponent>(new MeshComponent);
		self->onAddedToScene.addHandler(self);
		self->onRemovedFromScene.addHandler(self);
		self->onAddedToObject.addHandler(self);
		self->onRemovedFromObject.addHandler(self);
		return self;
	}

	std::shared_ptr<IO::GFX::Mesh> MeshComponent::getMesh() const {
		return mesh;
	}
	
	std::shared_ptr<IO::GFX::GraphicsProgram> MeshComponent::getGraphicsProgram() const {
		return program;
	}

	void MeshComponent::setMesh(std::shared_ptr<IO::GFX::Mesh> value) {
		mesh = value;
		drawCall->setMesh(value);
	}

	void MeshComponent::setGraphicsProgram(std::shared_ptr<IO::GFX::GraphicsProgram> value) {
		program = value;
		drawCall->setProgram(value);
	}

	void MeshComponent::handleAddedToObject(std::shared_ptr<Object> evtObj) {
		if(inScene) return;
		std::shared_ptr<EComponentAdded> evt = std::static_pointer_cast<EComponentAdded>(evtObj);
		std::shared_ptr<Scene> scn = evt->getObject()->getScene();
		if(scn == nullptr) return;
		inScene = true;
		scn->getRenderFrame()->addDraw(drawCall);
	}
	
	void MeshComponent::handleRemovedFromObject(std::shared_ptr<Object> evtObj) {
		if(!inScene) return;
		std::shared_ptr<EComponentRemoved> evt = std::static_pointer_cast<EComponentRemoved>(evtObj);
		std::shared_ptr<Scene> scn = evt->getObject()->getScene();
		if(scn == nullptr) return;
		inScene = false;
		scn->getRenderFrame()->removeDraw(drawCall);
	}

	void MeshComponent::handleAddedToScene(std::shared_ptr<Object> evtObj) {
		if(inScene) return;
		inScene = true;

		std::shared_ptr<EAddedToScene> evt = std::static_pointer_cast<EAddedToScene>(evtObj);
		evt->getScene()->getRenderFrame()->addDraw(drawCall);
	}
	
	void MeshComponent::handleRemovedFromScene(std::shared_ptr<Object> evtObj) {
		if(!inScene) return;
		inScene = false;

		std::shared_ptr<ERemovedFromScene> evt = std::static_pointer_cast<ERemovedFromScene>(evtObj);
		evt->getScene()->getRenderFrame()->removeDraw(this->drawCall);
	}

	void MeshComponent::handleDraw(std::shared_ptr<Object> evt) {
		std::shared_ptr<GameObject> obj = getObject();
		if(obj == nullptr) return;

		drawCall->setModelMatrix(obj->calculateModelMatrix());
	}
}
