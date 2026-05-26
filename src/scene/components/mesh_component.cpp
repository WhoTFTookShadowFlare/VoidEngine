#include "ve/io/gfx/mesh.hpp"
#include "ve/io/gfx/program_uniform.hpp"
#include "ve/scene/components/mesh.hpp"
#include "ve/io/gfx/graphics_program.hpp"
#include "ve/scene/scene.hpp"
#include "ve/scene/components/camera.hpp"
#include <glm/ext/matrix_float4x4.hpp>
#include <iostream>
#include <memory>
#include <optional>

namespace VoidEngine::Scene::Components {
	using namespace std;
	MeshComponent::MeshComponent() {}

	std::shared_ptr<MeshComponent> MeshComponent::create() {
		auto self = std::shared_ptr<MeshComponent>(new MeshComponent);
		self->onDraw += self;
		return self;
	}

	void MeshComponent::onEvent(Events::EComponentDraw& draw) {
		if(program == nullptr) return;
		if(mesh == nullptr) return;

		std::vector<glm::mat4> defaultMatrix = { glm::mat4(1.0f) };
		if(draw.scene->getCamera()) {
			vector<glm::mat4> matrixPass = { glm::mat4(1.0f) };
			if(uProjection) {
				matrixPass[0] = std::static_pointer_cast<ACamera>(
					draw.scene->getCamera()->getFirstComponentOfInstance(&ACamera::ClassData)
				)->getProjection(draw.window);
				program->setUniform(uProjection.value(), matrixPass);
			}
			if(uView) {
				matrixPass[0] = std::static_pointer_cast<ACamera>(
					draw.scene->getCamera()->getFirstComponentOfInstance(&ACamera::ClassData)
				)->getView(draw.scene->getCamera());
				program->setUniform(uView.value(), matrixPass);
			}
		} else {
			if(uProjection) program->setUniform(uProjection.value(), defaultMatrix);
			if(uView) program->setUniform(uView.value(), defaultMatrix);
		}
		if(uModel) {
			vector<glm::mat4> model = { draw.object->getModelMatrix() };
			program->setUniform(uModel.value(), model);
		}

		program->draw(mesh);
	}

	std::shared_ptr<VoidEngine::IO::GFX::Mesh> MeshComponent::getMesh() {
		return mesh;
	}

	std::shared_ptr<VoidEngine::IO::GFX::GraphicsProgram> MeshComponent::getProgram() {
		return program;
	}

	void MeshComponent::setMesh(std::shared_ptr<VoidEngine::IO::GFX::Mesh> mesh) {
		this->mesh = mesh;
	}

	void MeshComponent::setProgram(std::shared_ptr<VoidEngine::IO::GFX::GraphicsProgram> program) {
		using VoidEngine::IO::GFX::UniformType;

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

	const ComponentClass MeshComponent::ClassData = {
		.name = "MeshComponent",
	};
}

