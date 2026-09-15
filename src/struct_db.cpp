#include "ve/variant.hpp"
#include <cstddef>
#include <string>
#include <ve/struct_db.hpp>
#include <print>

namespace VoidEngine {
	const StructMember* StructData::getMember(std::string memberName) const {
		for(const auto& member : members)
			if(member.name == memberName) return &member;
		return nullptr;
	}

	const size_t StructData::offsetOf(std::string memberName) const {
		size_t offset = 0;

		for(const auto& member : members) {
			if(member.name == memberName) break;

			offset += (member.type == VariantType::STRUCT) ? member.data->sizeOf() : getVariantTypeSize(member.type);
		}

		return offset;
	}

	const VariantType StructData::typeOf(std::string memberName) const {
		for(const auto& member : members) {
			if(member.name == memberName) return member.type;
		}
		return VariantType::NIL;
	}

	const size_t StructData::sizeOf() const {
		size_t size = 0;

		for(const auto& member : members) {
			size += (member.type == VariantType::STRUCT) ? member.data->sizeOf() : getVariantTypeSize(member.type);
		}

		return size;
	}

	Struct::Struct(const StructData* strData, std::shared_ptr<void> data) {
		this->strData = strData;
		this->data = data;
	}

	void Struct::set(std::string member, Variant data) {
	
	}

	Variant Struct::get(std::string member) const {
		const StructMember* strMember = strData->getMember(member);
		if(strMember == nullptr) return nullptr;

		size_t offset = strData->offsetOf(member);
		VariantType type = strMember->type;
		
		void* addr = static_cast<void*>(static_cast<int8_t*>(data.get()) + offset);
		switch(type) {
		case VariantType::INT: {
			return *static_cast<int32_t*>(addr);
		} break;
		case VariantType::FLOAT: {
			return *static_cast<float*>(addr);
		} break;
		case VariantType::BOOL: {
			return *static_cast<bool*>(addr);
		} break;
		case VariantType::STRUCT: {
			return Struct(strMember->data, std::shared_ptr<void>(addr, [](void*) {}));
		} break;
		}

		std::println("[ERR] Unsupported type for struct {}", (int) type);
		return nullptr;
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
