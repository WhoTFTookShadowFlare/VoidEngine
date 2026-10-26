#pragma once

#include <ve/event/event.hpp>
#include <ve/io/gfx/render_frame.hpp>

namespace VoidEngine::Scene {
	class Scene;
	class GameObject;
	namespace Components {
		class AObjectComponent;
	}

	class EObjectRenamed final : public Event::AEvent {
		friend class GameObject;
		VE_CLASS(EObjectRenamed);
	private:
		std::shared_ptr<GameObject> obj = nullptr;
		std::string oldName = "";

		EObjectRenamed() = default;

		Variant scr_getObject(void) const;
		Variant scr_getOldName(void) const;
	public:
		static std::shared_ptr<EObjectRenamed> create();

		std::shared_ptr<GameObject> getObject() const;
		std::string getOldName() const;

		bool isSetup() const override;
	};

	class EChildAdded final : public Event::AEvent {
		friend class GameObject;
		VE_CLASS(EChildAdded);
	private:
		std::shared_ptr<GameObject> parent = nullptr;
		std::shared_ptr<GameObject> child = nullptr;

		EChildAdded() = default;

		Variant scr_getParent(void) const;
		Variant scr_getChild(void) const;
	public:
		static std::shared_ptr<EChildAdded> create();

		std::shared_ptr<GameObject> getParent() const;
		std::shared_ptr<GameObject> getChild() const;

		bool isSetup() const override;
	};

	class EParented final : public Event::AEvent {
		friend class GameObject;
		VE_CLASS(EParented);
	private:
		std::shared_ptr<GameObject> parent = nullptr;
		std::shared_ptr<GameObject> child = nullptr;

		EParented() = default;

		Variant scr_getParent(void) const;
		Variant scr_getChild(void) const;
	public:
		static std::shared_ptr<EParented> create();

		std::shared_ptr<GameObject> getParent() const;
		std::shared_ptr<GameObject> getChild() const;

		bool isSetup() const override;
	};

	class EChildRemoved final : public Event::AEvent {
		friend class GameObject;
		VE_CLASS(EChildRemoved);
	private:
		std::shared_ptr<GameObject> parent = nullptr;
		std::shared_ptr<GameObject> child = nullptr;

		EChildRemoved() = default;

		Variant scr_getParent(void) const;
		Variant scr_getChild(void) const;

	public:
		static std::shared_ptr<EChildRemoved> create();

		std::shared_ptr<GameObject> getParent() const;
		std::shared_ptr<GameObject> getChild() const;

		bool isSetup() const override;
	};

	class EAddedToScene final : public Event::AEvent {
		friend class Scene;
		VE_CLASS(EAddedToScene);
	private:
		std::shared_ptr<Scene> scene = nullptr;

		Variant scr_getScene(void) const;

		EAddedToScene() = default;
	public:
		static std::shared_ptr<EAddedToScene> create();

		std::shared_ptr<Scene> getScene() const;

		bool isSetup() const override;
	};

	class ERemovedFromScene final : public Event::AEvent {
		friend class Scene;
		VE_CLASS(ERemovedFromScene);
	private:
		std::shared_ptr<Scene> scene = nullptr;
		std::shared_ptr<GameObject> object = nullptr;

		Variant scr_getObject(void) const;
		Variant scr_getScene(void) const;

		ERemovedFromScene() = default;
	public:
		static std::shared_ptr<ERemovedFromScene> create();

		std::shared_ptr<GameObject> getObject() const;
		std::shared_ptr<Scene> getScene() const;

		bool isSetup() const override;
	};

	class EDraw final : public Event::AEvent {
		friend class Scene;
		VE_CLASS(EDraw);
	private:
		std::shared_ptr<IO::GFX::RenderFrame> frame = nullptr;

		EDraw() = default;

		Variant scr_getFrame(void) const;
	public:
		static std::shared_ptr<EDraw> create();

		std::shared_ptr<IO::GFX::RenderFrame> getFrame() const;

		bool isSetup() const override;
	};

	class EComponentAdded final : public Event::AEvent {
		friend class GameObject;
		VE_CLASS(EComponentAdded);
	private:
		std::shared_ptr<GameObject> object = nullptr;
		std::shared_ptr<Components::AObjectComponent> component = nullptr;

		EComponentAdded() = default;

		Variant scr_getObject(void) const;
		Variant scr_getComponent(void) const;
	public:
		static std::shared_ptr<EComponentAdded> create();

		std::shared_ptr<GameObject> getObject() const;
		std::shared_ptr<Components::AObjectComponent> getComponent() const;

		bool isSetup() const override;
	};
	
	class EComponentRemoved final : public Event::AEvent {
		friend class GameObject;
		VE_CLASS(EComponentRemoved);
	private:
		std::shared_ptr<GameObject> object = nullptr;
		std::shared_ptr<Components::AObjectComponent> component = nullptr;

		EComponentRemoved() = default;

		Variant scr_getObject(void) const;
		Variant scr_getComponent(void) const;
	public:
		static std::shared_ptr<EComponentRemoved> create();

		std::shared_ptr<GameObject> getObject() const;
		std::shared_ptr<Components::AObjectComponent> getComponent() const;

		bool isSetup() const override;
	};
}
