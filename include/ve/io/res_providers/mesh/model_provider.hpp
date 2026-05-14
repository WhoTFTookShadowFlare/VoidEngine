#pragma once

#include <stdexcept>
#include <format>
#include "ve/io/res_providers/mesh/a_provider.hpp"
#include "ve/io/res_providers/model/a_provider.hpp"

#include <print>

namespace VoidEngine::IO::ResourceProviders {
	class MeshModelProvider : public AMeshProvider {
	private:
		std::vector<VoidEngine::IO::GFX::Vertex> vertices;
		std::vector<uint32_t> indices;
	public:
		MeshModelProvider(AModelProvider& model, size_t meshIdx) {
			if(meshIdx >= model.getMeshCount())
				throw std::runtime_error(std::format("Cannot get mesh {} from model with {} meshes", meshIdx, model.getMeshCount()));

			aiMesh *mesh = model.getScene()->mMeshes[meshIdx];
			vertices = std::vector<VoidEngine::IO::GFX::Vertex>(mesh->mNumVertices);
			for(size_t idx = 0; idx < vertices.size(); idx++)
				vertices[idx].position = { mesh->mVertices[idx].x, mesh->mVertices[idx].y, mesh->mVertices[idx].z };

			for(size_t idx = 0; idx < vertices.size(); idx++)
				vertices[idx].normal = { mesh->mNormals[idx].x, mesh->mNormals[idx].y, mesh->mNormals[idx].z };

			for(size_t idx = 0; idx < vertices.size(); idx++)
				vertices[idx].UV = { mesh->mTextureCoords[0][idx].x, mesh->mTextureCoords[0][idx].y };

			if(mesh->mColors != nullptr) for (size_t idx = 0; idx < vertices.size(); idx++)
				vertices[idx].color = { 1, 1, 1, 1 };

			indices = std::vector<uint32_t>(3 * mesh->mNumFaces);
			for(size_t faceIdx = 0; faceIdx < mesh->mNumFaces; faceIdx++) {
				indices[faceIdx * 3 + 0] = mesh->mFaces[faceIdx].mIndices[0];
				indices[faceIdx * 3 + 1] = mesh->mFaces[faceIdx].mIndices[1];
				indices[faceIdx * 3 + 2] = mesh->mFaces[faceIdx].mIndices[2];
			}
		}

		std::vector<VoidEngine::IO::GFX::Vertex> getVertices() { return vertices; }
		std::vector<uint32_t> getIndices() { return indices; }
	};
}
