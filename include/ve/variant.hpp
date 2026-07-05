#pragma once

#include <cstddef>
#include <cstdint>
#include <exception>
#include <glm/ext/vector_float2.hpp>
#include <glm/ext/vector_float3.hpp>
#include <glm/ext/vector_float4.hpp>
#include <memory>
#include <expected>

namespace VoidEngine {
	class Object;

	enum VariantType : uint8_t {
		NIL,
		INT,
		FLOAT,
		BOOL,
		STRING,
		ARRAY,
		MAP,
		OBJECT,

		VEC2,
		VEC3,
		VEC4
	};

	class TypeError final : public std::exception {
	private:
		VariantType expected, got;
	public:
		TypeError(VariantType expected, VariantType got);

		const std::string message() const noexcept;
	};

	class Variant final {
	private:
		const VariantType type;
		void* data;
	public:
		Variant();
		Variant(std::nullptr_t);
		Variant(int32_t);
		Variant(float);
		Variant(bool);
		Variant(std::string);
		// Variant(uint32_t);
		// Variant(uint32_t);
		Variant(std::shared_ptr<Object>);

		Variant(glm::vec2);
		Variant(glm::vec3);
		Variant(glm::vec4);

		~Variant();

		constexpr bool isType(VariantType type);

		bool isNil() const;
		bool isInt() const;
		bool isFloat() const;
		bool isBool() const;
		bool isString() const;
		bool isArray() const;
		bool isMap() const;
		bool isObject() const;

		bool isVec2() const;
		bool isVec3() const;
		bool isVec4() const;

		std::expected<int32_t, TypeError> asInt();
		std::expected<float, TypeError> asFloat();
		std::expected<bool, TypeError> asBool();
		std::expected<std::string, TypeError> asString();
		// std::expected<, TypeError> asArray();
		// std::expected<, TypeError> asMap();
		std::expected<std::shared_ptr<Object>, TypeError> asObject();

		std::expected<glm::vec2, TypeError> asVec2();
		std::expected<glm::vec3, TypeError> asVec3();
		std::expected<glm::vec4, TypeError> asVec4();
	};
}
