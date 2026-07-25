#pragma once

#include "glm/ext/matrix_float4x4.hpp"
#include "ve/io/gfx/light.hpp"
#include "ve/io/gfx/mesh.hpp"
#include "ve/io/gfx/render_target.hpp"
#include <memory>
#include <vector>

namespace VoidEngine::IO::GFX {
	struct FrameDrawEntry final {
	private:
		std::shared_ptr<Mesh> mesh;
		std::shared_ptr<GraphicsProgram> program;
		glm::mat4 modelMatrix;
	public:
		FrameDrawEntry(std::shared_ptr<Mesh>, std::shared_ptr<GraphicsProgram>, glm::mat4 modelMatrix);

		std::shared_ptr<Mesh> getMesh() const;
		std::shared_ptr<GraphicsProgram> getProgram() const;
		glm::mat4 getModelMatrix() const;
	};

	class RenderFrame final {
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

		std::vector<FrameDrawEntry> draws = {};

		glm::mat4 projection = glm::mat4(1.0f);
		glm::mat4 view = glm::mat4(1.0f);

		std::shared_ptr<IRenderTarget> target;

		RenderFrame();
	public:
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
		void addDraw(std::shared_ptr<Mesh>, std::shared_ptr<GraphicsProgram>, glm::mat4 modelMatrix);

		void render() const;
	};
}
