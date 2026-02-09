#include "ve/io/gfx/texture.hpp"
#include "ve/io/gfx/texture_provider.hpp"
#include <cstdint>

namespace VoidEngine::IO::GFX::OpenGL {
	class GLTexture : public Texture {
		uint32_t texture = 0;
		bool filtered = false;
	public:
		GLTexture(uint8_t slot);
		~GLTexture();

		void bindTexture();
		void setTextureProvider(ATextureProvider&);

		void setFiltered(bool);
		bool isFiltered();
	};
}

