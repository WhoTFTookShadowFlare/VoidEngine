#pragma once

#include "ve/io/gfx/render_target.hpp"
#include <SDL3/SDL_video.h>
#include <glm/ext/vector_int2.hpp>
#include <memory>

#include "ve/io/gfx/opengl/backend.hpp"

namespace VoidEngine::IO {
	class Window : public GFX::ARenderTarget {
		friend class GFX::OpenGL::RendererOpenGL;
	public:
		struct CreationOptions {
			glm::ivec2 size = { 800, 600 };
			std::string title = "VoidEngine";
			bool resizable = true;
			bool borderless = false;
			bool alwaysOnTop = false;
			bool utility = false;
		};
	private:
		SDL_Window *window = nullptr;
	
		Window(CreationOptions&);
	public:
		~Window();
		static std::shared_ptr<Window> create(CreationOptions&);

		void setSize(glm::ivec2);
		glm::ivec2 getSize();

		void setPosition(glm::ivec2);
		glm::ivec2 getPosition();
	};
}

