#pragma once

#include "ve/class_db.hpp"
#include "ve/io/gfx/texture.hpp"
#include "ve/io/res_providers/texture/a_provider.hpp"
#include "ve/object.hpp"
#include <memory>

namespace VoidEngine::IO::GFX {
	class Material final : public Object {
		VE_CLASS(Material)
	private:
		std::shared_ptr<Texture> diffuse, specular;
		float shininess = 32.0f;

		Material();
	public:
		static std::shared_ptr<Material> create();

		void setAlbedo(std::shared_ptr<ResourceProviders::ATextureProvider>);
		std::shared_ptr<ResourceProviders::ATextureProvider> getAlbedo();

		void setDiffuse(std::shared_ptr<ResourceProviders::ATextureProvider>);
		std::shared_ptr<ResourceProviders::ATextureProvider> getDiffuse();

		void setSpecular(std::shared_ptr<ResourceProviders::ATextureProvider>);
		std::shared_ptr<ResourceProviders::ATextureProvider> getSpecular();

		void setShininess(float);
		float getShininess();

		std::shared_ptr<Texture> getAlbedoTexture();
		std::shared_ptr<Texture> getDiffuseTexture();
		std::shared_ptr<Texture> getSpecularTexture();
	};
}
