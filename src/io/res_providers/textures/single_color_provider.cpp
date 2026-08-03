#include "ve/io/res_providers/texture/single_color_provider.hpp"
#include "ve/io/res_providers/texture/a_provider.hpp"
#include <cmath>
#include <memory>

namespace VoidEngine::IO::ResourceProviders {
	SingleColorTextureProvider::SingleColorTextureProvider() {
	}

	std::shared_ptr<SingleColorTextureProvider> SingleColorTextureProvider::create() {
		return std::shared_ptr<SingleColorTextureProvider>(new SingleColorTextureProvider);
	}

	glm::ivec2 SingleColorTextureProvider::getSize() {
		return { 1, 1 };
	}

	std::vector<uint8_t> SingleColorTextureProvider::getData() {
		return {
			(uint8_t) std::round(color.x * 255.0),
			(uint8_t) std::round(color.y * 255.0),
			(uint8_t) std::round(color.z * 255.0),
			(uint8_t) std::round(color.w * 255.0)
		};
	}

	void SingleColorTextureProvider::setColor(VoidEngine::Variant value) {
		if(!value.isVec4()) return;
		color = value.asVec4().value();
		auto evt = std::make_shared<ETextureChanged>();
		onTextureChange.fireEvent(evt);
	}

	VoidEngine::Variant SingleColorTextureProvider::getColor() {
		return color;
	}
}
