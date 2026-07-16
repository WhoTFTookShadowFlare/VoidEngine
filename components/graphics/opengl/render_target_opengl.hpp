#pragma once

#include "ve/io/gfx/render_texture.hpp"
#include <cstdint>

namespace VoidEngine::IO::GFX::OpenGL {
	class GLRenderTarget : public RenderTexture {
	private:
		uint32_t FBO = 0;
	public:
		GLRenderTarget();
		~GLRenderTarget();

		void bindRenderTarget() override;
	};
}
