#pragma once

#include <ve/object.hpp>

#include <ve/physics2d/a_world_2d.hpp>

#include <ve/io/gfx/render_frame.hpp>

namespace VoidEngine::Scene {
	namespace Components {
		class APolyObjectComponent;
	}
	namespace Components::GFX {
		class ACameraComponent;
	}
	class GameObject;

	class Scene : public Object, public std::enable_shared_from_this<Scene> {
		VE_CLASS(Scene);
	private:
		std::shared_ptr<Physics2D::APhysics2DWorld> world2d;
		Scene();

		std::map<std::string, std::shared_ptr<GameObject>> objects;
		std::vector<std::shared_ptr<Components::APolyObjectComponent>> polyComponents;

		std::shared_ptr<IO::GFX::IRenderTarget> renderTarget = nullptr;
		std::shared_ptr<IO::GFX::RenderFrame> renderFrame = IO::GFX::RenderFrame::create();
		std::shared_ptr<Components::GFX::ACameraComponent> currentCamera = nullptr;

		void scr_setCurrentCamera(Variant);
		Variant scr_getCurrentCamera(void) const;

		Variant scr_getObject(std::vector<Variant>);
		Variant scr_addObject(std::vector<Variant>);
		Variant scr_removeObject(std::vector<Variant>);

		void updateCameraValues();

	public:
		static std::shared_ptr<Scene> create();
		~Scene();

		void handleObjectRenamed(std::shared_ptr<Object>);
		void handleCameraValueChanged(std::shared_ptr<Object>);

		std::shared_ptr<GameObject> getObject(std::string);
		void addObject(std::shared_ptr<GameObject>);
		void removeObject(std::string name);

		void update(double delta);
		void draw(double delta);

		void bindPolyObjectComponent(std::shared_ptr<Components::APolyObjectComponent>);
		
		std::shared_ptr<IO::GFX::IRenderTarget> getRenderTarget() const;
		void setRenderTarget(std::shared_ptr<IO::GFX::IRenderTarget>);

		std::shared_ptr<IO::GFX::RenderFrame> getRenderFrame() const;

		void setCurrentCamera(std::shared_ptr<Components::GFX::ACameraComponent>);
		std::shared_ptr<Components::GFX::ACameraComponent> getCurrentCamera() const;
	};
}
