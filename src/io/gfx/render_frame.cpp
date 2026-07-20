#include "ve/io/gfx/render_frame.hpp"
#include "glm/ext/matrix_float4x4.hpp"
#include "ve/io/gfx/renderer.hpp"
#include "ve/io/gfx/graphics_program.hpp"
#include <algorithm>
#include <memory>

namespace VoidEngine::IO::GFX {
	FrameDrawEntry::FrameDrawEntry(std::shared_ptr<Mesh> mesh, std::shared_ptr<GraphicsProgram> program, glm::mat4 modelMatrix)
		: mesh(mesh), program(program), modelMatrix(modelMatrix)
	{}

	std::shared_ptr<Mesh> FrameDrawEntry::getMesh() const {
		return mesh;
	}

	std::shared_ptr<GraphicsProgram> FrameDrawEntry::getProgram() const {
		return program;
	}

	glm::mat4 FrameDrawEntry::getModelMatrix() const {
		return modelMatrix;
	}

	RenderFrame::RenderFrame() {}

	std::shared_ptr<RenderFrame> RenderFrame::create() {
		return std::shared_ptr<RenderFrame>(new RenderFrame);
	}

	std::shared_ptr<IRenderTarget> RenderFrame::getTarget() {
		return target;
	}

	void RenderFrame::setTarget(std::shared_ptr<IRenderTarget> value) {
		target = value;
	}

	void RenderFrame::setProjection(glm::mat4 value) {
		projection = value;
	}

	glm::mat4 RenderFrame::getProjection() {
		return projection;
	}

	void RenderFrame::setView(glm::mat4 value) {
		view = value;
	}

	glm::mat4 RenderFrame::getView() {
		return view;
	}

	void RenderFrame::addDependency(std::shared_ptr<RenderFrame> frame) {
		dependancies.push_back(frame);
	}

	void RenderFrame::addLight(Light light) {
		lights.push_back(light);
	}

	void RenderFrame::addDraw(std::shared_ptr<Mesh> mesh, std::shared_ptr<GraphicsProgram> program, glm::mat4 modelMatrix) {
		draws.push_back({ mesh, program, modelMatrix });
	}

	void RenderFrame::render() const {
		std::for_each(dependancies.cbegin(), dependancies.cend(), [](const auto& frame) {
			frame->render();
		});

		auto renderer = Renderer::getInstance();
		renderer->bindRenderTarget(target);

		std::for_each(draws.cbegin(), draws.cend(), [&](const auto& draw) {
			if(draw.getProgram() == nullptr || draw.getMesh() == nullptr) return;

			auto program = draw.getProgram();

			auto optMatrix = program->queryUniform("uModel");
			if(optMatrix.has_value()) program->setUniform(optMatrix.value(), draw.getModelMatrix());
			optMatrix = program->queryUniform("uView");
			if(optMatrix.has_value()) program->setUniform(optMatrix.value(), view);
			optMatrix = program->queryUniform("uProjection");
			if(optMatrix.has_value()) program->setUniform(optMatrix.value(), projection);

			{
				auto optLight = program->queryUniform("light.position");
				if(!optLight.has_value()) {} //break;
				program->setUniform(optLight.value(), lights[0].position);

				optLight = program->queryUniform("light.ambient");
				program->setUniform(optLight.value(), lights[0].ambient);

				optLight = program->queryUniform("light.diffuse");
				program->setUniform(optLight.value(), lights[0].diffuse);

				optLight = program->queryUniform("light.specular");
				program->setUniform(optLight.value(), lights[0].specular);
			}

			program->draw(draw.getMesh());
		});
	}
}
