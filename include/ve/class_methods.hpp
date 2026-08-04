#pragma once

#include "ve/class_db.hpp"
#include "ve/variant.hpp"
#include "ve/object.hpp"
#include <memory>
#include <vector>

namespace VoidEngine {
	template<IsAbstractClass T>
	struct NativeMethod : public MethodBase {
		using Func = Variant (T::*)(std::vector<Variant>);
	private:
		const Func fn;
	public:
		NativeMethod(std::string name, Func fn) : MethodBase(name), fn(fn) {}

		Variant call(std::shared_ptr<Object> obj, std::vector<Variant> args) const {
			if(obj == nullptr) return nullptr; // TODO: Support for static functions.
			if(!obj->getClass()->instanceOf(&T::ClassData)) return nullptr;
			return (std::static_pointer_cast<T>(obj).get()->*fn)(args);
		}
	};
}
