#pragma once

#include <SDL3/SDL_video.h>
#include <glm/ext/vector_int2.hpp>
#include <memory>

#include "ve/io/gfx/opengl/backend.hpp"

namespace VoidEngine::IO {
	class Window final {
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
	
		bool closing = false;

		Window(CreationOptions&);
	public:
		~Window();
		static std::shared_ptr<Window> create(CreationOptions&);

		void setClosing(bool value);
		void close();
		bool isClosing() const;

		void setSize(glm::ivec2);
		glm::ivec2 getSize();

		void setPosition(glm::ivec2);
		glm::ivec2 getPosition();

		void setTitle(std::string);
		std::string getTitle();
	};
}

