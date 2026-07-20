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
		glm::vec3 ambient = { 1.0f, 1.0f, 1.0f };
		glm::vec3 diffuse = { 1.0f, 1.0f, 1.0f };
		glm::vec3 specular = { 1.0f, 1.0f, 1.0f };
		float shininess = 32.0f;

		Material();
	public:
		static const Class ClassData;
		virtual const Class* getClass() const { return &ClassData; }

		static std::shared_ptr<Material> create();

		void setAlbedo(std::shared_ptr<ResourceProviders::ATextureProvider>);
		std::shared_ptr<ResourceProviders::ATextureProvider> getAlbedo();

		void setAmbient(glm::vec3);
		glm::vec3 getAmbient();

		void setDiffuse(glm::vec3);
		glm::vec3 getDiffuse();

		void setSpecular(glm::vec3);
		glm::vec3 getSpecular();

		void setShininess(float);
		float getShininess();

		std::shared_ptr<Texture> getAlbedoTexture();
	};
}
