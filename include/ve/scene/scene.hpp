#pragma once

#include "ve/io/gfx/light.hpp"
#include "ve/io/gfx/render_frame.hpp"
#include "ve/io/gfx/render_target.hpp"
#include "ve/object.hpp"
#include "ve/scene/game_object.hpp"
#include <memory>
#include <map>
#include <vector>
#include <string>
#include <filesystem>

namespace VoidEngine::IO {
	class Window;
}

namespace VoidEngine::Scene::Components {
	class ACamera;
}

namespace VoidEngine::Scene {
	class Scene final : public Object, public std::enable_shared_from_this<Scene> {
		VE_CLASS(Scene)

		std::map<std::string, std::shared_ptr<GameObject>> objects = {};

		std::shared_ptr<GameObject> currentCamera = nullptr;

		IO::GFX::DirectionalLight light = {
			{
				{ 1.0f, 1.0f, 1.0f },
				{ 1.0f, 1.0f, 1.0f }
			},
			{ -0.5f, -1.0f, -0.5f },
		};
	public:
		static std::shared_ptr<Scene> create();
		static std::shared_ptr<Scene> loadFrom(std::filesystem::path);

		std::shared_ptr<GameObject> getObject(std::string name);
		void addObject(std::shared_ptr<GameObject> obj);

		std::shared_ptr<GameObject> getObjectFromPath(std::string path);

		std::vector<std::shared_ptr<GameObject>> getObjects();

		void setCamera(std::shared_ptr<GameObject>);
		std::shared_ptr<GameObject> getCamera();

		IO::GFX::DirectionalLight getDirectionalLight();
		void setDirectionalLight(IO::GFX::DirectionalLight);

		std::shared_ptr<IO::GFX::RenderFrame> draw(double delta, std::shared_ptr<IO::GFX::IRenderTarget> target);
	};
}
