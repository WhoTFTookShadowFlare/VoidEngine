#pragma once

#include "ve/io/gfx/mesh.hpp"
#include <memory>
namespace VoidEngine::IO::GFX::Dummy {
	class DummyMesh final : public Mesh {
	private:
		DummyMesh();

		void draw();
	protected:
		void buildMesh();
	public:
		static std::shared_ptr<DummyMesh> create();
	};
}
