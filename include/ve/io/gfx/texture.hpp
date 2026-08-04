#pragma once

#include "ve/io/res_providers/texture/a_provider.hpp"
#include "ve/object.hpp"
#include <cstdint>
#include <memory>

namespace VoidEngine::IO::GFX {
	class Texture : public Object {
	private:
		uint8_t slot;
	protected:
		std::shared_ptr<ResourceProviders::ATextureProvider> textureProvider;
	public:
		static const Class ClassData;
		virtual const Class* getClass() const { return &ClassData; }

		Texture(uint8_t slot) : slot(slot) {}
		virtual ~Texture() {}

		uint8_t getTextureSlot() { return slot; }

		virtual void setFiltered(bool) = 0;
		virtual bool isFiltered() = 0;

		virtual void bindTexture() = 0;
		virtual void setTextureProvider(std::shared_ptr<ResourceProviders::ATextureProvider>) = 0;
		std::shared_ptr<ResourceProviders::ATextureProvider> getTextureProvider();
	};
}

