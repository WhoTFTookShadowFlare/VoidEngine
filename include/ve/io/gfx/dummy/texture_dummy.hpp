#pragma once

#include "ve/io/gfx/texture.hpp"
#include <memory>

namespace VoidEngine::IO::GFX::Dummy {
	class DummyTexture final : public Texture {
	private:
		DummyTexture();

		bool filtered = true;
	public:
		static std::shared_ptr<DummyTexture> create();

		void setFiltered(bool);
		bool isFiltered();

		void bindTexture();
		void setTextureProvider(std::shared_ptr<ResourceProviders::ATextureProvider>);
	};
}
