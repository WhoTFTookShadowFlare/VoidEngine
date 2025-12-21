#pragma once

#include <glm/ext/vector_float4.hpp>

namespace VoidEngine::IO::GFX {
	class IRenderTarget {
	public:
		virtual void bindRenderTarget() = 0;
		virtual void setClearColor(glm::vec4 color) = 0;
	};
}
