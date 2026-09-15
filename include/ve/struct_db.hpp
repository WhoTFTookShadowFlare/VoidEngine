#pragma once

#include "ve/variant.hpp"
#include <cstddef>
#include <string>
#include <vector>

namespace VoidEngine {
	struct StructData;

	struct StructMember final {
		const std::string name;
		const VariantType type;
		const StructData* data; // Used only when type == VariantType::STRUCT
	};

	struct StructData final {
		const std::string name;
		const std::vector<StructMember> members;

		const size_t offsetOf(std::string memberName) const;
		const size_t sizeOf() const;
	};

	struct Struct final {
	private:
		const StructData* strData;
		std::shared_ptr<void> data;
	public:
		Struct(const StructData* strData, std::shared_ptr<void> data);
		
		void set(std::string member, Variant data);
		Variant get(std::string member) const;
	};

	extern StructData Vec2Data;
	extern StructData Vec3Data;
	extern StructData Vec4Data;
}
