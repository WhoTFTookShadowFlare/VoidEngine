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

	Struct::Struct(const StructData* strData, void* data) {
		this->strData = strData;
		this->data = std::shared_ptr<void>(data, [](void*) {});
	}

	const StructData* Struct::getData() const {
		return strData;
	}

	const void* Struct::raw() const {
		return data.get();
	}

	void Struct::set(std::string member, Variant value) {
		const StructMember* strMember = strData->getMember(member);
		if (strMember == nullptr) {
			std::println("[ERR] struct {} has no member {}", strData->name, member);
			return;
		}

		size_t offset = strData->offsetOf(member);
		VariantType type = strMember->type;
		if(value.getType() != type) {
			std::println("[ERR] Struct expected type {}, got {}", (uint8_t) type, (uint8_t) value.getType());
			return;
		}

		void* addr = static_cast<void*>(static_cast<int8_t*>(data.get()) + offset);
		switch(type) {
		case VariantType::INT: {
			*static_cast<int32_t*>(addr) = value.asInt().value();
			return;
		} break;
		case VariantType::FLOAT: {
			*static_cast<float*>(addr) = value.asFloat().value();
			return;
		} break;
		case VariantType::BOOL: {
			*static_cast<bool*>(addr) = value.asBool().value();
			return;
		} break;
		}

		std::println("[ERR] Cannot set struct member of type {}", (int) type);
	}

	Variant Struct::get(std::string member) const {
		const StructMember* strMember = strData->getMember(member);
		if(strMember == nullptr) {
			std::println("[ERR] struct {} has no member {}", strData->name, member);
			return nullptr;
		}

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
			return std::make_shared<Struct>(strMember->data, std::shared_ptr<void>(addr, [](void*) {}));
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
