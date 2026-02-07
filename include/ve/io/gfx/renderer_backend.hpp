#pragma once

#include "ve/io/gfx/mesh.hpp"
#include "ve/io/gfx/render_target.hpp"
#include "ve/io/gfx/shader.hpp"
#include "ve/io/gfx/shader_source_provider.hpp"
#include "ve/io/gfx/texture.hpp"
#include <cstdint>

namespace VoidEngine::IO {
	class Window;
	namespace GFX {
		class ARendererBackend {
		public:
			virtual ~ARendererBackend() {}
			virtual void setupWindow(Window*) = 0;
			virtual void destroyWindow(Window*) = 0;
			virtual void setRenderTarget(ARenderTarget*) = 0;
			virtual void swapBuffers(Window*) = 0;

			virtual Mesh *createMesh() = 0;
			
			virtual Shader *createShader(ShaderType, AShaderSourceProvider&) = 0;
			virtual GraphicsProgram *createGraphicsProgram(Shader *vertex, Shader *fragment) = 0;

			virtual Texture *createTexture(uint8_t slot) = 0;
		};
	}
}

