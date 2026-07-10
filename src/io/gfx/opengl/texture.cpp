#include "ve/io/gfx/opengl/texture.hpp"
#include "ve/io/gfx/texture.hpp"
#include "ve/io/res_providers/texture/a_provider.hpp"
#include <cstdint>
#include <glbinding/gl/enum.h>
#include <glbinding/gl/functions.h>
#include <glbinding/gl46core/gl.h>
#include <glm/ext/vector_int2.hpp>

namespace VoidEngine::IO::GFX::OpenGL {
	using namespace gl;

	void GLTexture::uploadTexture() {
		auto provider =  getTextureProvider();
		if(provider == nullptr) {
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 0, 0, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);
			return;
		}

		glm::ivec2 size = provider->getSize();
		std::vector<uint8_t> data = provider->getData();
		bindTexture();
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, size.x, size.y, 0, GL_RGBA, GL_UNSIGNED_BYTE, data.data());
		glGenerateTextureMipmap(texture);
	}

	GLTexture::GLTexture(uint8_t slot) : Texture(slot) {
		glGenTextures(1, &texture);
	}

	GLTexture::~GLTexture() {
		glDeleteTextures(1, &texture);
	}

	void GLTexture::bindTexture() {
		glActiveTexture(GL_TEXTURE0 + getTextureSlot());
		glBindTexture(GL_TEXTURE_2D, texture);
	}

	void GLTexture::setTextureProvider(std::shared_ptr<ResourceProviders::ATextureProvider> textureData) {
		if(textureProvider) textureProvider->onTextureChange -= weak_from_this();
		textureProvider = textureData;
		if(textureProvider) textureProvider->onTextureChange += weak_from_this();
		uploadTexture();
	}

	void GLTexture::setFiltered(bool value) {
		bindTexture();
		GLenum filterMode = (value ? GL_LINEAR : GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, filterMode);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, filterMode);
		filtered = value;
	}

	bool GLTexture::isFiltered() {
		return filtered;
	}

	void GLTexture::onEvent(ResourceProviders::ETextureChanged& evt) {
		uploadTexture();
	}
}
