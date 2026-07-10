#include "ve/io/gfx/texture.hpp"

namespace VoidEngine::IO::GFX {
	std::shared_ptr<ResourceProviders::ATextureProvider> Texture::getTextureProvider() {
		return textureProvider;
	}
}
