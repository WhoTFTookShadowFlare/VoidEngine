#include "ve/io/gfx/dummy/texture_dummy.hpp"
#include "ve/io/gfx/texture.hpp"
#include <memory>

namespace VoidEngine::IO::GFX::Dummy {
	const Class DummyTexture::ClassData = {
		.name = "DummyTexture"
	};

	DummyTexture::DummyTexture() : Texture(0) {}

	std::shared_ptr<DummyTexture> DummyTexture::create() {
		return std::shared_ptr<DummyTexture>(new DummyTexture);
	}

	void DummyTexture::setFiltered(bool value) { filtered = value; }
	bool DummyTexture::isFiltered() { return filtered; }

	void DummyTexture::bindTexture() {}
	void DummyTexture::setTextureProvider(std::shared_ptr<ResourceProviders::ATextureProvider> provider) { textureProvider = provider; }
}