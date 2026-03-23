#include "ve/io/gfx/mesh.hpp"
#include "ve/io/gfx/program_uniform.hpp"
#include "ve/scene/components/mesh.hpp"
#include "ve/io/gfx/graphics_program.hpp"
#include "ve/scene/components/transform.hpp"
#include <glm/ext/matrix_float4x4.hpp>
#include <iostream>
#include <memory>
#include <optional>

namespace VoidEngine::Scene::Components {
	void MeshComponent::draw(double delta) {
		if(program == nullptr) return;
		if(mesh == nullptr) return;

		vector<glm::mat4> defaultMatrix = { glm::mat4(1.0f) };
		if(uProjection) program->setUniform(uProjection.value(), defaultMatrix);
		if(uView) program->setUniform(uView.value(), defaultMatrix);
		if(uModel) {
			if(transform) {
				vector<glm::mat4> model = { transform->getMatrix() };
				program->setUniform(uModel.value(), model);
			} else {
				program->setUniform(uModel.value(), defaultMatrix);
			}
		}

		program->draw(mesh);
	}

	void MeshComponent::update(double delta) {	}

	shared_ptr<TransformComponent> MeshComponent::getTransform() {
		return transform;
	}

	shared_ptr<Mesh> MeshComponent::getMesh() {
		return mesh;
	}

	shared_ptr<GraphicsProgram> MeshComponent::getProgram() {
		return program;
	}

	void MeshComponent::setTransform(shared_ptr<TransformComponent> transform) {
		this->transform = transform;
	}

	void MeshComponent::setMesh(shared_ptr<Mesh> mesh) {
		this->mesh = mesh;
	}

	void MeshComponent::setProgram(shared_ptr<GraphicsProgram> program) {
		this->program = program;
		uProjection = nullopt;
		uView = nullopt;
		uModel = nullopt;

		if(program == nullptr) return;

		for(auto& uniform : program->getUniforms()) {
			if(uniform.getName() == "uModel") {
				if(uniform.getType() != UniformType::MATRIX_4X4F) {
					cerr << "[WARN] Uniform uModel was not of type MATRIX_4X4F" << endl;
					continue;
				}
				uModel = uniform;
				continue;
			}
			if(uniform.getName() == "uView") {
				if(uniform.getType() != UniformType::MATRIX_4X4F) {
					cerr << "[WARN] Uniform uView was not of type MATRIX_4X4F" << endl;
					continue;
				}
				uView = uniform;
				continue;
			}
			if(uniform.getName() == "uProjection") {
				if(uniform.getType() != UniformType::MATRIX_4X4F) {
					cerr << "[WARN] Uniform uProjection was not of type MATRIX_4X4F" << endl;
					continue;
				}
				uProjection = uniform;
				continue;
			}
		}
	
		if(uProjection == nullopt) std::cerr << "[WARN] uProjection was not found in the shader" << std::endl;
		if(uView == nullopt) std::cerr << "[WARN] uView was not found in the shader" << std::endl;
		if(uModel == nullopt) std::cerr << "[WARN] uModel was not found in the shader" << std::endl;
	}
}

