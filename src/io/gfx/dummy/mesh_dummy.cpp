#include "ve/io/gfx/dummy/mesh_dummy.hpp"
#include "ve/io/gfx/mesh.hpp"
#include <memory>

namespace VoidEngine::IO::GFX::Dummy {
	const Class DummyMesh::ClassData = {
		.name = "DummyMesh",
		.super = &Mesh::ClassData
	};

	DummyMesh::DummyMesh() {}

	void DummyMesh::draw() {}
	void DummyMesh::buildMesh() {}
	
	std::shared_ptr<DummyMesh> DummyMesh::create() {
		return std::shared_ptr<DummyMesh>(new DummyMesh);
	}
}
