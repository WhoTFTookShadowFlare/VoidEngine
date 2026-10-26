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

	void AFrameDrawCall::draw() {
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
		std::for_each(dependancies.cbegin(), dependancies.cend(), [](const auto& frame) {
			frame->render();
		});

		auto renderer = Renderer::getInstance();
		renderer->bindRenderTarget(target);

		std::for_each(draws.cbegin(), draws.cend(), [](const std::weak_ptr<AFrameDrawCall>& weakDrawCall) {
			const std::shared_ptr<AFrameDrawCall> drawCall = weakDrawCall.lock();
			if(drawCall == nullptr) return;
			if(drawCall->getProgram() == nullptr) return;

			std::shared_ptr<GraphicsProgram> program = drawCall->getProgram();

			std::optional<Uniform> uView = program->queryUniform("uView");
			std::optional<Uniform> uProjection = program->queryUniform("uProjection");

			if(uView.has_value()) program->setUniform(uView.value(), glm::mat4(1.0f));
			if(uProjection.has_value()) program->setUniform(uProjection.value(), glm::mat4(1.0f));

			drawCall->draw();
		});

		/*std::for_each(draws.cbegin(), draws.cend(), [&](const auto& draw) {
			if(draw.getProgram() == nullptr || draw.getMesh() == nullptr) return;

			auto program = draw.getProgram();

			auto optMatrix = program->queryUniform("uModel");
			if(optMatrix.has_value()) program->setUniform(optMatrix.value(), draw.getModelMatrix());
			optMatrix = program->queryUniform("uView");
			if(optMatrix.has_value()) program->setUniform(optMatrix.value(), view);
			optMatrix = program->queryUniform("uProjection");
			if(optMatrix.has_value()) program->setUniform(optMatrix.value(), projection);

			auto optLight = program->queryUniform("directionalLight.direction");
			if(optLight.has_value()) {
				program->setUniform(optLight.value(), directionalLight.direction);

				optLight = program->queryUniform("directionalLight.light.diffuse");
				program->setUniform(optLight.value(), directionalLight.diffuse);

				optLight = program->queryUniform("directionalLight.light.specular");
				program->setUniform(optLight.value(), directionalLight.specular);
			}

			optLight = program->queryUniform("pointLightCount");
			if(optLight) {
				program->setUniform(optLight.value(), (int32_t) pointLights.size());
				for(size_t idx = 0; idx < glm::min((size_t) MAX_POINT_LIGHTS, pointLights.size()); idx++) {
					auto optLight = program->queryUniform(std::format("pointLight[{}].position", idx));
					program->setUniform(optLight.value(), pointLights[idx].position);

					optLight = program->queryUniform(std::format("pointLight[{}].light.diffuse", idx));
					program->setUniform(optLight.value(), pointLights[idx].diffuse);

					optLight = program->queryUniform(std::format("pointLight[{}].light.specular", idx));
					program->setUniform(optLight.value(), pointLights[idx].specular);
				
					optLight = program->queryUniform(std::format("pointLight[{}].constant", idx));
					program->setUniform(optLight.value(), pointLights[idx].constant);

					optLight = program->queryUniform(std::format("pointLight[{}].linear", idx));
					program->setUniform(optLight.value(), pointLights[idx].linear);
					
					optLight = program->queryUniform(std::format("pointLight[{}].quadratic", idx));
					program->setUniform(optLight.value(), pointLights[idx].quadratic);
				}
			}

			optLight = program->queryUniform("spotLightCount");
			if(optLight) {
				program->setUniform(optLight.value(), (int32_t) spotLights.size());
				for(size_t idx = 0; idx < glm::min((size_t) MAX_SPOT_LIGHTS, spotLights.size()); idx++) {
					auto optLight = program->queryUniform(std::format("spotLight[{}].position", idx));
					program->setUniform(optLight.value(), spotLights[idx].position);
	
					optLight = program->queryUniform(std::format("spotLight[{}].direction", idx));
					program->setUniform(optLight.value(), spotLights[idx].direction);
	
					optLight = program->queryUniform(std::format("spotLight[{}].cutoffAngle", idx));
					program->setUniform(optLight.value(), glm::cos(glm::radians(spotLights[idx].cutoffAngle)));
	
					optLight = program->queryUniform(std::format("spotLight[{}].outerCutoffAngle", idx));
					program->setUniform(optLight.value(), glm::cos(glm::radians(spotLights[idx].outerCutoffAngle)));
	
					optLight = program->queryUniform(std::format("spotLight[{}].light.diffuse", idx));
					program->setUniform(optLight.value(), spotLights[idx].diffuse);

					optLight = program->queryUniform(std::format("spotLight[{}].light.specular", idx));
					program->setUniform(optLight.value(), spotLights[idx].specular);
				
					optLight = program->queryUniform(std::format("spotLight[{}].constant", idx));
					program->setUniform(optLight.value(), spotLights[idx].constant);

					optLight = program->queryUniform(std::format("spotLight[{}].linear", idx));
					program->setUniform(optLight.value(), spotLights[idx].linear);

					optLight = program->queryUniform(std::format("spotLight[{}].quadratic", idx));
					program->setUniform(optLight.value(), spotLights[idx].quadratic);
				}
			}

			program->draw(draw.getMesh());
		});*/
	}
}
