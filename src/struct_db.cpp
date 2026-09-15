#include "ve/variant.hpp"
#include <cstddef>
#include <string>
#include <ve/struct_db.hpp>

namespace VoidEngine {
	const size_t StructData::offsetOf(std::string memberName) const {
		size_t offset = 0;

		for(const auto& member : members) {
			if(member.name == memberName) break;

			offset += (member.type == VariantType::STRUCT) ? member.data->sizeOf() : getVariantTypeSize(member.type);
		}

		return offset;
	}

	const size_t StructData::sizeOf() const {
		size_t size = 0;

		for(const auto& member : members) {
			size += (member.type == VariantType::STRUCT) ? member.data->sizeOf() : getVariantTypeSize(member.type);
		}

		return size;
	}

	StructData Vec2Data = {
		.name = "Vec2",
		.members = {
			{ .name = "x", .type = VariantType::FLOAT },
			{ .name = "y", .type = VariantType::FLOAT },
		}
	};

	StructData Vec3Data = {
		.name = "Vec3",
		.members = {
			{ .name = "x", .type = VariantType::FLOAT },
			{ .name = "y", .type = VariantType::FLOAT },
			{ .name = "z", .type = VariantType::FLOAT },
		}
	};

	StructData Vec4Data = {
		.name = "Vec4",
		.members = {
			{ .name = "x", .type = VariantType::FLOAT },
			{ .name = "y", .type = VariantType::FLOAT },
			{ .name = "z", .type = VariantType::FLOAT },
			{ .name = "w", .type = VariantType::FLOAT },
		}
	};
}
