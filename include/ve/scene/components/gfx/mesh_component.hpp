#pragma once

#include <ve/scene/components/a_mono_object_component.hpp>

#include <ve/object.hpp>
#include <ve/io/gfx/render_frame.hpp>

#include <ve/io/gfx/mesh.hpp>

#include <glm/ext/matrix_float4x4.hpp>

namespace VoidEngine::Scene::Components::GFX {
	class MeshComponentDrawCall final : public IO::GFX::AFrameDrawCall {
		VE_CLASS(MeshComponentDrawCall);
	private:
		std::shared_ptr<IO::GFX::Mesh> mesh = nullptr;
		glm::mat4 modelMatrix = glm::mat4(1.0f);

		MeshComponentDrawCall() = default;
	public:
		static std::shared_ptr<MeshComponentDrawCall> create();

		void draw() override;

		std::shared_ptr<IO::GFX::Mesh> getMesh() const;
		void setMesh(std::shared_ptr<IO::GFX::Mesh>);

		glm::mat4 getModelMatrix() const;
		void setModelMatrix(glm::mat4);
	};

	class MeshComponent final : public AMonoObjectComponent {
		VE_CLASS(MeshComponent);
	private:
		std::shared_ptr<MeshComponentDrawCall> drawCall = MeshComponentDrawCall::create();

		std::shared_ptr<IO::GFX::Mesh> mesh = nullptr;
		std::shared_ptr<IO::GFX::GraphicsProgram> program = nullptr;

		bool inScene = false;

		MeshComponent() = default;
	public:
		static std::shared_ptr<MeshComponent> create();

		std::shared_ptr<IO::GFX::Mesh> getMesh() const;
		std::shared_ptr<IO::GFX::GraphicsProgram> getGraphicsProgram() const;

		void setMesh(std::shared_ptr<IO::GFX::Mesh>);
		void setGraphicsProgram(std::shared_ptr<IO::GFX::GraphicsProgram>);

		void handleAddedToObject(std::shared_ptr<Object> evt);
		void handleRemovedFromObject(std::shared_ptr<Object> evt);
		void handleAddedToScene(std::shared_ptr<Object> evt);
		void handleRemovedFromScene(std::shared_ptr<Object> evt);
		void handleDraw(std::shared_ptr<Object> evt);
	};
}
