#include "ve/scene/ui/ui_draw.hpp"

namespace VoidEngine::Scene::Events {
	EUIDraw::EUIDraw(
		double delta, std::shared_ptr<IO::GFX::IRenderTarget> target,
		std::shared_ptr<Scene> scene, std::shared_ptr<UIElement> parentElement
	) : delta(delta), target(target), scene(scene), parentElement(parentElement)
	{}
}
