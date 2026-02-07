#pragma once

#include "ve/io/gfx/texture_provider.hpp"
#include <cstdint>

namespace VoidEngine::IO::GFX {
	class Texture {
		uint8_t slot;
	public:
		Texture(uint8_t slot) : slot(slot) {}
		virtual ~Texture() {}

		uint8_t getTextureSlot() { return slot; }

		virtual void bindTexture() = 0;
		virtual void setTextureProvider(ATextureProvider&) = 0;
		virtual void setFiltered(bool) = 0;
	};
}

