#pragma once

#include <ve/object.hpp>

#include <ve/physics2d/a_world_2d.hpp>

#include <ve/io/gfx/render_frame.hpp>

namespace VoidEngine::Scene {
    class GameObject;

    class Scene : public Object, public std::enable_shared_from_this<Scene> {
        VE_CLASS(Scene);
    private:
        std::shared_ptr<Physics2D::APhysics2DWorld> world2d;
        Scene();

        std::map<std::string, std::shared_ptr<GameObject>> objects;

        std::shared_ptr<IO::GFX::RenderFrame> renderFrame = IO::GFX::RenderFrame::create();

    public:
        static std::shared_ptr<Scene> create();
        ~Scene();

        void handleObjectRenamed(std::shared_ptr<Object>);

        std::shared_ptr<GameObject> getObject(std::string);
        void addObject(std::shared_ptr<GameObject>);
        void removeObject(std::string name);

        void draw(double delta);
        std::shared_ptr<IO::GFX::RenderFrame> getRenderFrame();
    };
}
