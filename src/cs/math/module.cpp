#include "ve/cs/math/module.hpp"
#include "ve/cs/interface.hpp"
#include "ve/math/rect2.hpp"
#include <array>
#include <cstdint>
#include <glm/ext/vector_float2.hpp>
#include <iostream>
#include <mono-2.0/mono/metadata/class.h>
#include <mono-2.0/mono/metadata/loader.h>
#include <mono-2.0/mono/metadata/object-forward.h>
#include <mono-2.0/mono/metadata/object.h>

namespace VoidEngine::CS::Math {
	CSharpInterface *interface = nullptr;
	MonoClass *Vec2fClass = nullptr;
	MonoClass *Vec2iClass = nullptr;
	MonoClass *Rect2fClass = nullptr;
	MonoClass *Rect2iClass = nullptr;

	MonoObject *Rect2f_GetEndPosition(MonoObject *self);
	bool Rect2f_CollidesWith(MonoObject *self, MonoObject *other);
	bool Rect2f_ContainsPoint(MonoObject *self, MonoObject *point);
	MonoObject *Rect2f_GetCenter(MonoObject *self);
	float Rect2f_GetVerticalCenter(MonoObject *self);
	float Rect2f_GetHorizontalCenter(MonoObject *self);
	MonoArray *Rect2f_GetRectVertices(MonoObject *self);
	MonoArray *Rect2f_SplitHorizontally(MonoObject *self, float point);
	MonoArray *Rect2f_SplitVertically(MonoObject *self, float point);

	MonoObject *Rect2f_Round(MonoObject *self);
	MonoObject *Rect2f_Floor(MonoObject *self);
	MonoObject *Rect2f_Ceil(MonoObject *self);

	MonoObject *Rect2i_GetEndPosition(MonoObject *self);
	bool Rect2i_CollidesWith(MonoObject *self, MonoObject *other);
	bool Rect2i_ContainsPoint(MonoObject *self, MonoObject *point);
	MonoObject *Rect2i_GetCenter(MonoObject *self);
	int Rect2i_GetVerticalCenter(MonoObject *self);
	int Rect2i_GetHorizontalCenter(MonoObject *self);
	MonoArray *Rect2i_GetRectVertices(MonoObject *self);
	MonoArray *Rect2i_SplitHorizontally(MonoObject *self, int point);
	MonoArray *Rect2i_SplitVertically(MonoObject *self, int point);

	void initModule_Engine_Math(void) {
		mono_add_internal_call("VoidEngine.Math.Rect2f::GetEndPosition", (void*) Rect2f_GetEndPosition);
		mono_add_internal_call("VoidEngine.Math.Rect2f::CollidesWith", (void*) Rect2f_CollidesWith);
		mono_add_internal_call("VoidEngine.Math.Rect2f::ContainsPoint", (void*) Rect2f_ContainsPoint);
		mono_add_internal_call("VoidEngine.Math.Rect2f::GetCenter", (void*) Rect2f_GetCenter);
		mono_add_internal_call("VoidEngine.Math.Rect2f::GetVerticalCenter", (void*) Rect2f_GetVerticalCenter);
		mono_add_internal_call("VoidEngine.Math.Rect2f::GetHorizontalCenter", (void*) Rect2f_GetHorizontalCenter);
		mono_add_internal_call("VoidEngine.Math.Rect2f::GetRectVertices", (void*) Rect2f_GetRectVertices);
		mono_add_internal_call("VoidEngine.Math.Rect2f::SplitHorizontally", (void*) Rect2f_SplitHorizontally);
		mono_add_internal_call("VoidEngine.Math.Rect2f::SplitVertically", (void*) Rect2f_SplitVertically);
		mono_add_internal_call("VoidEngine.Math.Rect2f::Round", (void*) Rect2f_Round);
		mono_add_internal_call("VoidEngine.Math.Rect2f::Floor", (void*) Rect2f_Floor);
		mono_add_internal_call("VoidEngine.Math.Rect2f::Ceil", (void*) Rect2f_Ceil);

		mono_add_internal_call("VoidEngine.Math.Rect2i::GetEndPosition", (void*) Rect2i_GetEndPosition);
		mono_add_internal_call("VoidEngine.Math.Rect2i::CollidesWith", (void*) Rect2i_CollidesWith);
		mono_add_internal_call("VoidEngine.Math.Rect2i::ContainsPoint", (void*) Rect2i_ContainsPoint);
		mono_add_internal_call("VoidEngine.Math.Rect2i::GetCenter", (void*) Rect2i_GetCenter);
		mono_add_internal_call("VoidEngine.Math.Rect2i::GetVerticalCenter", (void*) Rect2i_GetVerticalCenter);
		mono_add_internal_call("VoidEngine.Math.Rect2i::GetHorizontalCenter", (void*) Rect2i_GetHorizontalCenter);
		mono_add_internal_call("VoidEngine.Math.Rect2i::GetRectVertices", (void*) Rect2i_GetRectVertices);
		mono_add_internal_call("VoidEngine.Math.Rect2i::SplitHorizontally", (void*) Rect2i_SplitHorizontally);
		mono_add_internal_call("VoidEngine.Math.Rect2i::SplitVertically", (void*) Rect2i_SplitVertically);

		interface = CSharpInterface::getInstance();
		Vec2fClass = interface->getClass("VoidEngine.Math", "Vec2f");
		Vec2iClass = interface->getClass("VoidEngine.Math", "Vec2i");
		Rect2fClass = interface->getClass("VoidEngine.Math", "Rect2f");
		Rect2iClass = interface->getClass("VoidEngine.Math", "Rect2i");
	}

	MonoObject *vec2fToMonoObject(glm::vec2 from) {
		MonoObject *obj = interface->instanceClass(Vec2fClass);
		if(obj == nullptr) {
			return nullptr;
		}

		MonoClassField *x = mono_class_get_field_from_name(Vec2fClass, "x");
		if(x == nullptr) {
			return nullptr;
		}

		MonoClassField *y = mono_class_get_field_from_name(Vec2fClass, "y");
		if(y == nullptr) {
			return nullptr;
		}

		mono_field_set_value(obj, x, &from.x);
		mono_field_set_value(obj, y, &from.y);
		return obj;
	}

	MonoObject *rect2fToMonoObject(VoidEngine::Math::Rect2f rect) {
		MonoObject *obj = interface->instanceClass(Rect2fClass);
		if(obj == nullptr) {
			return nullptr;
		}

		MonoClassField *position = mono_class_get_field_from_name(Rect2fClass, "position");
		if(position == nullptr) {
			return nullptr;
		}

		MonoClassField *size = mono_class_get_field_from_name(Rect2fClass, "size");
		if(size == nullptr) {
			return nullptr;
		}

		MonoObject *posVal = vec2fToMonoObject(rect.position);
		MonoObject *sizeVal = vec2fToMonoObject(rect.size);
		mono_field_set_value(obj, position, &posVal);
		mono_field_set_value(obj, size, &sizeVal);

		return nullptr;
	}

	MonoObject *vec2iToMonoObject(glm::ivec2 from) {
		MonoObject *obj = interface->instanceClass(Vec2iClass);
		if(obj == nullptr) {
			return nullptr;
		}

		MonoClassField *x = mono_class_get_field_from_name(Vec2iClass, "x");
		if(x == nullptr) {
			return nullptr;
		}

		MonoClassField *y = mono_class_get_field_from_name(Vec2iClass, "y");
		if(y == nullptr) {
			return nullptr;
		}

		mono_field_set_value(obj, x, &from.x);
		mono_field_set_value(obj, y, &from.y);
		return obj;

	}

	MonoObject *rect2iToMonoObject(VoidEngine::Math::Rect2i rect) {
		MonoObject *obj = interface->instanceClass(Rect2iClass);
		if(obj == nullptr) {
			return nullptr;
		}

		MonoClassField *position = mono_class_get_field_from_name(Rect2iClass, "position");
		if(position == nullptr) {
			return nullptr;
		}

		MonoClassField *size = mono_class_get_field_from_name(Rect2iClass, "size");
		if(size == nullptr) {
			return nullptr;
		}

		MonoObject *posVal = vec2iToMonoObject(rect.position);
		MonoObject *sizeVal = vec2iToMonoObject(rect.size);
		mono_field_set_value(obj, position, &posVal);
		mono_field_set_value(obj, size, &sizeVal);

		return nullptr;
	}

	glm::vec2 vec2fFromMonoObject(MonoObject *obj) {
		if(obj == nullptr) {
			std::cerr << "[WARN] vec2FromMonoObject got nullptr for obj" << std::endl;
			return { 0, 0 };
		}

		if(!mono_object_isinst(obj, Vec2fClass)) {
			std::cerr << "[ERR] vec2FromMonoObject was not passed a MonoObject of the C# type" << std::endl;
			return { 0, 0 };
		}

		MonoClassField *xPos = mono_class_get_field_from_name(Vec2fClass, "x");
		if(xPos == nullptr) {
			std::cerr << "[ERR] Failed to get field 'x'" << std::endl;
			return { 0, 0 };
		}

		MonoClassField *yPos = mono_class_get_field_from_name(Vec2fClass, "y");
		if(yPos == nullptr) {
			std::cerr << "[ERR] Failed to get field 'y'" << std::endl;
			return { 0, 0 };
		}

		glm::vec2 v = { 0, 0 };
		mono_field_get_value(obj, xPos, &v.x);
		mono_field_get_value(obj, yPos, &v.y);
		return v;
	}

	VoidEngine::Math::Rect2f rect2fFromMonoObject(MonoObject *obj) {
		if(obj == nullptr) {
			std::cerr << "[WARN] rect2fFromMonoObject got nullptr for obj" << std::endl;
			return { { 0, 0 }, { 0, 0 } };
		}

		MonoClassField *position = mono_class_get_field_from_name(Rect2fClass, "position");
		if(position == nullptr) {
			std::cerr << "[ERR] Failed to get field 'position'" << std::endl;
			return { { 0, 0 }, { 0, 0 } };
		}

		MonoClassField *size = mono_class_get_field_from_name(Rect2fClass, "size");
		if(size == nullptr) {
			std::cerr << "[ERR] Failed to get field 'size'" << std::endl;
			return { { 0, 0 }, { 0, 0 } };
		}

		MonoObject *posObj = nullptr, *sizeObj = nullptr;
		mono_field_get_value(obj, position, &posObj);
		mono_field_get_value(obj, size, &sizeObj);
		return {
			vec2fFromMonoObject(posObj),
			vec2fFromMonoObject(sizeObj)
		};
	}

	glm::ivec2 vec2iFromMonoObject(MonoObject *obj) {
		if(obj == nullptr) {
			std::cerr << "[WARN] vec2iFromMonoObject got nullptr for obj" << std::endl;
			return { 0, 0 };
		}

		if(!mono_object_isinst(obj, Vec2iClass)) {
			std::cerr << "[ERR] vec2iFromMonoObject was not passed a MonoObject of the C# type" << std::endl;
			return { 0, 0 };
		}

		MonoClassField *xPos = mono_class_get_field_from_name(Vec2iClass, "x");
		if(xPos == nullptr) {
			std::cerr << "[ERR] Failed to get field 'x'" << std::endl;
			return { 0, 0 };
		}

		MonoClassField *yPos = mono_class_get_field_from_name(Vec2iClass, "y");
		if(yPos == nullptr) {
			std::cerr << "[ERR] Failed to get field 'y'" << std::endl;
			return { 0, 0 };
		}

		glm::ivec2 v = { 0, 0 };
		mono_field_get_value(obj, xPos, &v.x);
		mono_field_get_value(obj, yPos, &v.y);
		return v;

	}

	VoidEngine::Math::Rect2i rect2iFromMonoObject(MonoObject *obj) {
		if(obj == nullptr) {
			std::cerr << "[WARN] rect2iFromMonoObject got nullptr for obj" << std::endl;
			return { { 0, 0 }, { 0, 0 } };
		}
		MonoClassField *position = mono_class_get_field_from_name(Rect2iClass, "position");
		if(position == nullptr) {
			std::cerr << "[ERR] Failed to get field 'position'" << std::endl;
			return { { 0, 0 }, { 0, 0 } };
		}

		MonoClassField *size = mono_class_get_field_from_name(Rect2iClass, "size");
		if(size == nullptr) {
			std::cerr << "[ERR] Failed to get field 'size'" << std::endl;
			return { { 0, 0 }, { 0, 0 } };
		}

		MonoObject *posObj = nullptr, *sizeObj = nullptr;
		mono_field_get_value(obj, position, &posObj);
		mono_field_get_value(obj, size, &sizeObj);
		return {
			vec2iFromMonoObject(posObj),
			vec2iFromMonoObject(sizeObj)
		};
	}

	MonoClass *getVec2fClass() {
		return Vec2fClass;
	}

	MonoClass *getRect2fClass() {
		return Rect2fClass;
	}

	MonoClass *getVec2iClass() {
		return Vec2iClass;
	}

	MonoClass *getRect2iClass() {
		return Rect2iClass;
	}

	MonoObject *Rect2f_GetEndPosition(MonoObject *self) {
		VoidEngine::Math::Rect2f rect = rect2fFromMonoObject(self);
		return vec2fToMonoObject(rect.getEndPosition());
	}

	bool Rect2f_CollidesWith(MonoObject *self, MonoObject *other) {
		VoidEngine::Math::Rect2f LHS = rect2fFromMonoObject(self),
			RHS = rect2fFromMonoObject(other);
		return LHS.collidesWith(RHS);
	}

	bool Rect2f_ContainsPoint(MonoObject *self, MonoObject *point) {
		VoidEngine::Math::Rect2f rect = rect2fFromMonoObject(self);
		return rect.containsPoint(vec2fFromMonoObject(point));
	}

	MonoObject *Rect2f_GetCenter(MonoObject *self) {
		VoidEngine::Math::Rect2f rect = rect2fFromMonoObject(self);
		return vec2fToMonoObject(rect.getCenter());
	}

	float Rect2f_GetVerticalCenter(MonoObject *self) {
		return rect2fFromMonoObject(self).getVerticalCenter();
	}

	float Rect2f_GetHorizontalCenter(MonoObject *self) {
		return rect2fFromMonoObject(self).getHorizontalCenter();
	}

	MonoArray *Rect2f_GetRectVertices(MonoObject *self) {
		CSharpInterface *interface = CSharpInterface::getInstance();
		VoidEngine::Math::Rect2f rect = rect2fFromMonoObject(self);
		std::array<glm::vec2, 4> vertices = rect.getRectVertices();

		MonoClass *vec2fCls = interface->getClass("VoidEngine.Math", "Vec2f");
		if(vec2fCls == nullptr) return nullptr;

		MonoArray *array = interface->allocArray(vec2fCls, 4);
		if(array == nullptr) return nullptr;

		for(uint8_t idx = 0; idx < 4; idx++)
			mono_array_setref(array, idx, vec2fToMonoObject(vertices[idx]));

		return array;
	}

	MonoArray *Rect2f_SplitHorizontally(MonoObject *self, float point) {
		CSharpInterface *interface = CSharpInterface::getInstance();
		VoidEngine::Math::Rect2f rect = rect2fFromMonoObject(self);
		std::array<VoidEngine::Math::Rect2f, 2> split = rect.splitHorizontally(point);

		MonoClass *rect2fCls = interface->getClass("VoidEngine.Math", "Rect2f");
		if(rect2fCls == nullptr) return nullptr;

		MonoArray *array = interface->allocArray(rect2fCls, 2);
		if(array == nullptr) return nullptr;

		for(uint8_t idx = 0; idx < 2; idx++)
			mono_array_setref(array, idx, rect2fToMonoObject(split[idx]));

		return array;
	}

	MonoArray *Rect2f_SplitVertically(MonoObject *self, float point) {
		CSharpInterface *interface = CSharpInterface::getInstance();
		VoidEngine::Math::Rect2f rect = rect2fFromMonoObject(self);
		std::array<VoidEngine::Math::Rect2f, 2> split = rect.splitVertically(point);

		MonoClass *rect2fCls = interface->getClass("VoidEngine.Math", "Rect2f");
		if(rect2fCls == nullptr) return nullptr;

		MonoArray *array = interface->allocArray(rect2fCls, 2);
		if(array == nullptr) return nullptr;

		for(uint8_t idx = 0; idx < 2; idx++)
			mono_array_setref(array, idx, rect2fToMonoObject(split[idx]));

		return array;
	}

	MonoObject *Rect2f_Round(MonoObject *self) {
		return rect2fToMonoObject(rect2fFromMonoObject(self).round<float>());
	}

	MonoObject *Rect2f_Floor(MonoObject *self) {
		return rect2fToMonoObject(rect2fFromMonoObject(self).floor<float>());
	}

	MonoObject *Rect2f_Ceil(MonoObject *self) {
		return rect2fToMonoObject(rect2fFromMonoObject(self).ceil<float>());
	}

	MonoObject *Rect2i_GetEndPosition(MonoObject *self) {
		VoidEngine::Math::Rect2i rect = rect2iFromMonoObject(self);
		return vec2iToMonoObject(rect.getEndPosition());
	}

	bool Rect2i_CollidesWith(MonoObject *self, MonoObject *other) {
		VoidEngine::Math::Rect2i LHS = rect2iFromMonoObject(self),
			RHS = rect2iFromMonoObject(other);
		return LHS.collidesWith(RHS);
	}

	bool Rect2i_ContainsPoint(MonoObject *self, MonoObject *point) {
		VoidEngine::Math::Rect2i rect = rect2iFromMonoObject(self);
		return rect.containsPoint(vec2iFromMonoObject(point));
	}

	MonoObject *Rect2i_GetCenter(MonoObject *self) {
		VoidEngine::Math::Rect2i rect = rect2iFromMonoObject(self);
		return vec2iToMonoObject(rect.getCenter());
	}

	int Rect2i_GetVerticalCenter(MonoObject *self) {
		return rect2iFromMonoObject(self).getVerticalCenter();
	}

	int Rect2i_GetHorizontalCenter(MonoObject *self) {
		return rect2iFromMonoObject(self).getHorizontalCenter();
	}

	MonoArray *Rect2i_GetRectVertices(MonoObject *self) {
		VoidEngine::Math::Rect2i rect = rect2iFromMonoObject(self);
		std::array<glm::ivec2, 4> vertices = rect.getRectVertices();

		MonoArray *array = interface->allocArray(Vec2iClass, 4);
		if(array == nullptr) return nullptr;

		for(uint8_t idx = 0; idx < 4; idx++)
			mono_array_setref(array, idx, vec2iToMonoObject(vertices[idx]));

		return array;
	}

	MonoArray *Rect2i_SplitHorizontally(MonoObject *self, int point) {
		VoidEngine::Math::Rect2i rect = rect2iFromMonoObject(self);
		std::array<VoidEngine::Math::Rect2i, 2> split = rect.splitHorizontally(point);

		MonoArray *array = interface->allocArray(Rect2iClass, 2);
		if(array == nullptr) return nullptr;

		for(uint8_t idx = 0; idx < 2; idx++)
			mono_array_setref(array, idx, rect2iToMonoObject(split[idx]));

		return array;
	}

	MonoArray *Rect2i_SplitVertically(MonoObject *self, int point) {
		CSharpInterface *interface = CSharpInterface::getInstance();
		VoidEngine::Math::Rect2i rect = rect2iFromMonoObject(self);
		std::array<VoidEngine::Math::Rect2i, 2> split = rect.splitVertically(point);

		MonoArray *array = interface->allocArray(Rect2iClass, 2);
		if(array == nullptr) return nullptr;

		for(uint8_t idx = 0; idx < 2; idx++)
			mono_array_setref(array, idx, rect2iToMonoObject(split[idx]));

		return array;
	}
}

