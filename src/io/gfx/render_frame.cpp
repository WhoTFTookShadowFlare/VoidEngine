#include "ve/io/gfx/render_frame.hpp"
#include "glm/common.hpp"
#include "glm/ext/matrix_float4x4.hpp"
#include "glm/trigonometric.hpp"
#include "ve/io/gfx/light.hpp"
#include "ve/io/gfx/renderer.hpp"
#include "ve/io/gfx/graphics_program.hpp"
#include <algorithm>
#include <memory>

namespace VoidEngine::IO::GFX {
	const ::VoidEngine::Class AFrameDrawCall::ClassData = {
		.name = "AFrameDrawCall",
		.super = &Object::ClassData,
		.flags = ClassFlags::NONE
	};

	std::shared_ptr<GraphicsProgram> AFrameDrawCall::getProgram() const {
		return program;
	}

	void AFrameDrawCall::setProgram(std::shared_ptr<GraphicsProgram> value) {
		program = value;
	}

	void AFrameDrawCall::draw(std::shared_ptr<const RenderFrame>) {
		assert(false);
	}

	const ::VoidEngine::Class RenderFrame::ClassData = {
		.name = "RenderFrame",
		.super = &Object::ClassData,
		.flags = ClassFlags::FINAL
	};

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

	void RenderFrame::setDirectionalLight(DirectionalLight value) {
		directionalLight = value;
	}

	DirectionalLight RenderFrame::getDirectionalLight() {
		return directionalLight;
	}

	void RenderFrame::addPointLight(PointLight light) {
		pointLights.push_back(light);
	}

	void RenderFrame::addSpotLight(SpotLight light) {
		spotLights.push_back(light);
	}

	void RenderFrame::addDraw(std::shared_ptr<AFrameDrawCall> drawCall) {
		draws.push_back(drawCall);
	}

	void RenderFrame::removeDraw(std::shared_ptr<AFrameDrawCall> drawCall) {
		draws.erase(std::remove_if(draws.begin(), draws.end(), [&drawCall](const std::weak_ptr<AFrameDrawCall> iter) {
			return iter.lock() == nullptr || iter.lock() == drawCall;
		}));
	}

	void RenderFrame::render() const {
		if(target == nullptr) return;

		std::for_each(dependancies.cbegin(), dependancies.cend(), [](const auto& frame) {
			frame->render();
		});

		auto renderer = Renderer::getInstance();
		renderer->bindRenderTarget(target);

		std::for_each(draws.cbegin(), draws.cend(), [&](const std::weak_ptr<AFrameDrawCall>& weakDrawCall) {
			const std::shared_ptr<AFrameDrawCall> drawCall = weakDrawCall.lock();
			if(drawCall == nullptr) return;
			if(drawCall->getProgram() == nullptr) return;

			std::shared_ptr<GraphicsProgram> program = drawCall->getProgram();

			std::optional<Uniform> uView = program->queryUniform("uView");
			std::optional<Uniform> uProjection = program->queryUniform("uProjection");

			if(uView.has_value()) program->setUniform(uView.value(), view);
			if(uProjection.has_value()) program->setUniform(uProjection.value(), projection);

			// TODO: Add lights to draw calls
			drawCall->draw(shared_from_this());
		});
	}
}
