#include "ve/variant.hpp"
#include "glm/ext/vector_float2.hpp"
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
		data = std::make_shared<int32_t>(value);
	}

	Variant::Variant(float value) : type(VariantType::FLOAT) {
		data = std::make_shared<float>(value);
	}

	Variant::Variant(bool value) : type(VariantType::BOOL) {
		data = std::make_shared<bool>(value);
	}

	Variant::Variant(std::string value) : type(VariantType::STRING) {
		data = std::make_shared<std::string>(value);
	}

	// Variant::Variant(uint32_t);
	// Variant::Variant(uint32_t);
	
	Variant::Variant(std::shared_ptr<Object> value) : type(VariantType::OBJECT) {
		data = std::make_shared<std::shared_ptr<Object>>(value);
	}

	Variant::Variant(glm::vec2 value) : type(VariantType::VEC2) { data = std::make_shared<glm::vec2>(value); }
	Variant::Variant(glm::vec3 value) : type(VariantType::VEC3) { data = std::make_shared<glm::vec3>(value); }
	Variant::Variant(glm::vec4 value) : type(VariantType::VEC4) { data = std::make_shared<glm::vec4>(value); }

	Variant::~Variant() {	}

	constexpr bool Variant::isType(VariantType type) { return this->type == type; }

	bool Variant::isNil() const { return type == VariantType::NIL; }
	bool Variant::isInt() const { return type == VariantType::INT; }
	bool Variant::isFloat() const { return type == VariantType::FLOAT; }
	bool Variant::isBool() const { return type == VariantType::BOOL; }
	bool Variant::isString() const { return type == VariantType::STRING; }
	bool Variant::isArray() const { return type == VariantType::ARRAY; }
	bool Variant::isMap() const { return type == VariantType::MAP; }
	bool Variant::isObject() const { return type == VariantType::OBJECT; }

	bool Variant::isVec2() const { return type == VariantType::VEC2; }
	bool Variant::isVec3() const { return type == VariantType::VEC3; }
	bool Variant::isVec4() const { return type == VariantType::VEC4; }

	std::expected<int32_t, TypeError> Variant::asInt() {
		if(!isInt()) { return std::unexpected(TypeError(VariantType::INT, type)); }
		return int32_t(*(int32_t*) data.get());
	}

	std::expected<float, TypeError> Variant::asFloat() {
		if(!isFloat()) { return std::unexpected(TypeError(VariantType::FLOAT, type)); }
		return float(*(float*) data.get());
	}

	std::expected<bool, TypeError> Variant::asBool() {
		if(!isBool()) { return std::unexpected(TypeError(VariantType::BOOL, type)); }
		return bool(*(bool*) data.get());
	}

	std::expected<std::string, TypeError> Variant::asString() {
		if(!isString()) { return std::unexpected(TypeError(VariantType::STRING, type)); }
		return std::string(*(std::string*) data.get());
	}

	// std::expected<, TypeError> Variant::asArray() {}
	// std::expected<, TypeError> Variant::asMap() {}
	
	std::expected<std::shared_ptr<Object>, TypeError> Variant::asObject() {
		if(!isObject()) { return std::unexpected(TypeError(VariantType::OBJECT, type)); }
		return std::shared_ptr<Object>(*(std::shared_ptr<Object>*) data.get());
	}

	std::expected<glm::vec2, TypeError> Variant::asVec2() {
		if(!isVec2()) { return std::unexpected(TypeError(VariantType::VEC2, type)); }
		return glm::vec2(*(glm::vec2*) data.get());
	}
	
	std::expected<glm::vec3, TypeError> Variant::asVec3() {
		if(!isVec3()) { return std::unexpected(TypeError(VariantType::VEC3, type)); }
		return glm::vec3(*(glm::vec3*) data.get());
	}
	
	std::expected<glm::vec4, TypeError> Variant::asVec4() {
		if(!isVec4()) { return std::unexpected(TypeError(VariantType::VEC4, type)); }
		return glm::vec4(*(glm::vec4*) data.get());
	}
}
