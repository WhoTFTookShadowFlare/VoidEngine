#pragma once

namespace VoidEngine::IO::GFX {
	class IRenderTarget {
	private:
	public:
		virtual void bindRenderTarget() = 0;
	};
}
