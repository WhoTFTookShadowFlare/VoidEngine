#include "ve/io/gfx/texture.hpp"
#include "ve/class_db.hpp"

namespace VoidEngine::IO::GFX {
	const Class Texture::ClassData = {
		.name = "Texture",
		.super = &Object::ClassData
	};

	std::shared_ptr<ResourceProviders::ATextureProvider> Texture::getTextureProvider() {
		return textureProvider;
	}
}
