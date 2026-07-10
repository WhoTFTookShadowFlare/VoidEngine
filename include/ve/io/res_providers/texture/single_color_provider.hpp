#pragma once

#include "ve/io/res_providers/texture/a_provider.hpp"
#include "ve/variant.hpp"
#include <glm/ext/vector_float4.hpp>
#include <memory>

namespace VoidEngine::IO::ResourceProviders {
	class SingleColorTextureProvider final : public ATextureProvider {
	private:
		glm::vec4 color;

		SingleColorTextureProvider();
	public:
		static std::shared_ptr<SingleColorTextureProvider> create();

		glm::ivec2 getSize();
		std::vector<uint8_t> getData();

		void setColor(VoidEngine::Variant);
		VoidEngine::Variant getColor();
	};
}
