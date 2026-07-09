#pragma once

#include <memory>
#include "ui_element.hpp"
#include "ve/scene/ui/ui_element.hpp"
#include "ve/io/gfx/render_target.hpp"
#include "ve/scene/scene.hpp"

namespace VoidEngine::Scene::Events {
	class EUIDraw final {
	private:
	public:
		EUIDraw(
			double delta, std::shared_ptr<IO::GFX::IRenderTarget> target,
			std::shared_ptr<Scene> scene, std::shared_ptr<UIElement> parentElement
		);

		const double delta;
		const std::shared_ptr<IO::GFX::IRenderTarget> target;
		const std::shared_ptr<Scene> scene;
		const std::shared_ptr<UIElement> parentElement;
	};
}
