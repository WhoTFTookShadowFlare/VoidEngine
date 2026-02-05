#pragma once

#include "ve/io/gfx/mesh.hpp"
#include "ve/io/gfx/render_target.hpp"

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
		};
	}
}

