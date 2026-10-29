#pragma once

#include "glm/ext/matrix_float4x4.hpp"
#include "ve/io/gfx/light.hpp"
#include "ve/io/gfx/mesh.hpp"
#include "ve/io/gfx/render_target.hpp"
#include <memory>
#include <vector>

namespace VoidEngine::IO::GFX {
	class RenderFrame;

	class AFrameDrawCall : public Object {
		VE_CLASS(AFrameDrawCall);
	private:
		std::shared_ptr<GraphicsProgram> program = nullptr;

	public:
		std::shared_ptr<GraphicsProgram> getProgram() const;
		void setProgram(std::shared_ptr<GraphicsProgram>);

		virtual void draw(std::shared_ptr<const RenderFrame>);
	};

	class RenderFrame final : public Object, public std::enable_shared_from_this<RenderFrame> {
		VE_CLASS(RenderFrame);
	private:
		std::vector<std::shared_ptr<RenderFrame>> dependancies = {};

		DirectionalLight directionalLight = {
			{ 
				{ 1.0f, 1.0f, 1.0f },
				{ 1.0f, 1.0f, 1.0f }
			},
			{ 0.1f, -1.0f, -0.1f }
		};
		
		std::vector<PointLight> pointLights = {};
		std::vector<SpotLight> spotLights = {};

		std::vector<std::weak_ptr<AFrameDrawCall>> draws = {};

		glm::mat4 projection = glm::mat4(1.0f);
		glm::mat4 view = glm::mat4(1.0f);

		std::shared_ptr<IRenderTarget> target;

		RenderFrame() = default;
	public:
		const int32_t MAX_POINT_LIGHTS = 4;
		const int32_t MAX_SPOT_LIGHTS = 4;

		static std::shared_ptr<RenderFrame> create();

		std::shared_ptr<IRenderTarget> getTarget();
		void setTarget(std::shared_ptr<IRenderTarget>);

		void setProjection(glm::mat4);
		glm::mat4 getProjection();

		void setView(glm::mat4);
		glm::mat4 getView();

		void addDependency(std::shared_ptr<RenderFrame>);

		void setDirectionalLight(DirectionalLight);
		DirectionalLight getDirectionalLight();

		void addPointLight(PointLight);
		void addSpotLight(SpotLight);

		void addDraw(std::shared_ptr<AFrameDrawCall>);
		void removeDraw(std::shared_ptr<AFrameDrawCall>);

		void render() const;
	};
}
