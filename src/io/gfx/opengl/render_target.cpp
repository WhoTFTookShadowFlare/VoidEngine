#include "ve/io/gfx/opengl/render_target.hpp"

#include <glbinding/gl40/gl.h>

namespace VoidEngine::IO::GFX::OpenGL {
	GLRenderTarget::GLRenderTarget() {
		gl::glGenFramebuffers(1, &FBO);
	}

	GLRenderTarget::~GLRenderTarget() {
		gl::glDeleteFramebuffers(1, &FBO);
	}

	void GLRenderTarget::bindRenderTarget() {
		gl::glBindFramebuffer(gl::GL_FRAMEBUFFER, FBO);
	};
}
