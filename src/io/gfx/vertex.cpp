#include "ve/struct_db.hpp"
#include "ve/variant.hpp"
#include <ve/io/gfx/vertex.hpp>

namespace VoidEngine::IO::GFX {
	StructData VertexData = {
		.name = "Vertex",
		.members = {
			{ .name = "position",	.type = VariantType::STRUCT, .data = &Vec3Data },
			{ .name = "color",		.type = VariantType::STRUCT, .data = &Vec4Data },
			{ .name = "UV",			.type = VariantType::STRUCT, .data = &Vec2Data },
			{ .name = "normal",		.type = VariantType::STRUCT, .data = &Vec3Data },
		}
	};
}
