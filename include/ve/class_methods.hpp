#pragma once

#include "class_db.hpp"
#include "variant.hpp"
#include <memory>
#include <vector>

namespace VoidEngine {
	template<IsAbstractClass T>
	struct Method : public MethodBase {
		using Func = Variant (T::*)(std::vector<Variant>);
	private:
		const Func fn;
	public:
		Method(std::string name, Func fn) : MethodBase(name), fn(fn) {}

		Variant call(std::shared_ptr<Object> obj, std::vector<Variant> args) const {
			if(!obj->getClass()->instanceOf(&T::ClassData)) return nullptr;
			return (std::static_pointer_cast<T>(obj).get()->*fn)(args);
		}
	};
}
