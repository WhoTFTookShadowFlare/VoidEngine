#include "ve/io/gfx/material.hpp"
#include "ve/io/gfx/renderer.hpp"
#include "ve/io/gfx/texture.hpp"
#include "ve/io/res_providers/texture/a_provider.hpp"
#include <memory>

namespace VoidEngine::IO::GFX {
	const Class Material::ClassData = { .name = "Material" };

	Material::Material() {
		auto renderer = Renderer::getInstance();
		diffuse = renderer->createTexture(0);
		specular = renderer->createTexture(1);
	}

	std::shared_ptr<Material> Material::create() {
		auto self = std::shared_ptr<Material>(new Material);
		return self;
	}

	void Material::setDiffuse(std::shared_ptr<ResourceProviders::ATextureProvider> value) {
		diffuse->setTextureProvider(value);
	}

	std::shared_ptr<ResourceProviders::ATextureProvider> Material::getDiffuse() {
		return diffuse->getTextureProvider();
	}

	std::shared_ptr<Texture> Material::getDiffuseTexture() {
		return diffuse;
	}

	void Material::setSpecular(std::shared_ptr<ResourceProviders::ATextureProvider> value) {
		specular->setTextureProvider(value);
	}

	std::shared_ptr<ResourceProviders::ATextureProvider> Material::getSpecular() {
		return specular->getTextureProvider();
	}

	std::shared_ptr<Texture> Material::getSpecularTexture() {
		return specular;
	}

	void Material::setShininess(float value) {
		shininess = value;
	}

	float Material::getShininess() {
		return shininess;
	}
}
