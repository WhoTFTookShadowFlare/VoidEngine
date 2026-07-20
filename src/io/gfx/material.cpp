#include "ve/io/gfx/material.hpp"
#include "ve/io/gfx/renderer.hpp"
#include "ve/io/res_providers/texture/a_provider.hpp"
#include <memory>

namespace VoidEngine::IO::GFX {
	const Class Material::ClassData = { .name = "Material" };

	Material::Material() {
		auto renderer = Renderer::getInstance();
		albedo = renderer->createTexture(0);
	}

	std::shared_ptr<Material> Material::create() {
		auto self = std::shared_ptr<Material>(new Material);
		return self;
	}

	void Material::setAlbedo(std::shared_ptr<ResourceProviders::ATextureProvider> value) {
		albedo->setTextureProvider(value);
	}

	std::shared_ptr<ResourceProviders::ATextureProvider> Material::getAlbedo() {
		return albedo->getTextureProvider();
	}

	std::shared_ptr<Texture> Material::getAlbedoTexture() {
		return albedo;
	}

	void Material::setAmbient(glm::vec3 value) {
		ambient = value;
	}

	glm::vec3 Material::getAmbient() {
		return ambient;
	}

	void Material::setDiffuse(glm::vec3 value) {
		diffuse = value;
	}

	glm::vec3 Material::getDiffuse() {
		return diffuse;
	}

	void Material::setSpecular(glm::vec3 value) {
		specular = value;
	}

	glm::vec3 Material::getSpecular() {
		return specular;
	}

	void Material::setShininess(float value) {
		shininess = value;
	}

	float Material::getShininess() {
		return shininess;
	}
}
