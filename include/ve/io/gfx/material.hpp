#pragma once

#include "ve/class_db.hpp"
#include "ve/io/gfx/texture.hpp"
#include "ve/io/res_providers/texture/a_provider.hpp"
#include "ve/object.hpp"
#include <memory>

namespace VoidEngine::IO::GFX {
	class Material final : public Object {
	private:
		std::shared_ptr<Texture> albedo;

		Material();
	public:
		static const Class ClassData;
		virtual const Class* getClass() const { return &ClassData; }

		static std::shared_ptr<Material> create();

		void setAlbedo(std::shared_ptr<ResourceProviders::ATextureProvider>);
		std::shared_ptr<ResourceProviders::ATextureProvider> getAlbedo();

		std::shared_ptr<Texture> getAlbedoTexture();
	};
}
