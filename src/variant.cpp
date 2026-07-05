#include "ve/variant.hpp"
#include "ve/object.hpp"
#include <cstdint>
#include <expected>
#include <format>
#include <memory>
#include <print>
#include <string>

namespace VoidEngine {
	TypeError::TypeError(VariantType expected, VariantType got) : expected(expected), got(got)
	{}

	const std::string TypeError::message() const noexcept {
		return std::format("Expected type {}, got {}", (uint8_t) expected, (uint8_t) got);
	}

	Variant::Variant() : type(VariantType::NIL) {
		data = nullptr;
	}

	Variant::Variant(std::nullptr_t) : VoidEngine::Variant() {}

	Variant::Variant(int32_t value) : type(VariantType::INT) {
		data = new int32_t(value);
	}

	Variant::Variant(float value) : type(VariantType::FLOAT) {
		data = new float(value);
	}

	Variant::Variant(bool value) : type(VariantType::BOOL) {
		data = new bool(value);
	}

	Variant::Variant(std::string value) : type(VariantType::STRING) {
		data = new std::string(value);
	}

	// Variant::Variant(uint32_t);
	// Variant::Variant(uint32_t);
	
	Variant::Variant(std::shared_ptr<Object> value) : type(VariantType::OBJECT) {
		data = new std::shared_ptr<Object>(value);
	}

	Variant::~Variant() {
		switch(type) {
		case VariantType::NIL: break;
		case VariantType::INT: delete (int32_t*) data; break;
		case VariantType::FLOAT: delete (float*) data; break;
		case VariantType::BOOL: delete (bool*) data; break;
		case VariantType::STRING: delete (std::string*) data; break;
		// case VariantType::ARRAY: delete (bool*) data; break;
		// case VariantType::MAP: delete (bool*) data; break;
		case VariantType::OBJECT: delete (std::shared_ptr<Object>*) data; break;
		default:
			std::println("[ERR] Could not determine variant of type id: {}, memory leaked!", (uint8_t) type);
		}
	}

	constexpr bool Variant::isType(VariantType type) { return this->type == type; }

	bool Variant::isNil() const { return type == VariantType::NIL; }
	bool Variant::isInt() const { return type == VariantType::INT; }
	bool Variant::isFloat() const { return type == VariantType::FLOAT; }
	bool Variant::isBool() const { return type == VariantType::BOOL; }
	bool Variant::isString() const { return type == VariantType::STRING; }
	bool Variant::isArray() const { return type == VariantType::ARRAY; }
	bool Variant::isMap() const { return type == VariantType::MAP; }
	bool Variant::isObject() const { return type == VariantType::OBJECT; }

	std::expected<int32_t, TypeError> Variant::asInt() {
		if(!isInt()) { return std::unexpected(TypeError(VariantType::INT, type)); }
		return int32_t(*(int32_t*) data);
	}

	std::expected<float, TypeError> Variant::asFloat() {
		if(!isFloat()) { return std::unexpected(TypeError(VariantType::INT, type)); }
		return float(*(float*) data);
	}

	std::expected<bool, TypeError> Variant::asBool() {
		if(!isBool()) { return std::unexpected(TypeError(VariantType::INT, type)); }
		return bool(*(bool*) data);
	}

	std::expected<std::string, TypeError> Variant::asString() {
		if(!isString()) { return std::unexpected(TypeError(VariantType::INT, type)); }
		return std::string(*(std::string*) data);
	}

	// std::expected<, TypeError> Variant::asArray() {}
	// std::expected<, TypeError> Variant::asMap() {}
	
	std::expected<std::shared_ptr<Object>, TypeError> Variant::asObject() {
		if(!isObject()) { return std::unexpected(TypeError(VariantType::INT, type)); }
		return std::shared_ptr<Object>(*(std::shared_ptr<Object>*) data);
	}
}
