#pragma once

#include <memory>
#include <string>
#include <unordered_map>
#include <vector>
#include <functional>
#include <cassert>

#include "ve/scene/object_component.hpp"

namespace VoidEngine::Scene {
	struct Class {
		const char* name;

		const Class *super;
		std::vector<const Class*> childTypes;

		std::function<std::shared_ptr<AObjectComponent>()> create;

		bool operator==(Class RHS) const { return name == RHS.name; }

		bool instanceOf(const Class* cls) const {
			const Class *check = this;
			while(check != nullptr) {
				if(cls == check) return true;
				check = check->super;
			}
			return false;
		}

		bool isAbstract() const {
			return create == nullptr;
		}
	};

	class ClassDB {
	private:
		static std::shared_ptr<ClassDB> instance;

		std::unordered_map<std::string, const Class*> componentClasses;

		ClassDB();
	public:
		static std::shared_ptr<ClassDB> getInstance();

		const Class* getClassByName(std::string);

		template<IsAbstractObjectComponent component, IsAbstractObjectComponent parent>
		void registerAbstractClass() {
			Class *cls = (Class*) &component::ClassData;
			cls->super = &parent::ClassData;

			Class *parentCls = (Class*) &parent::ClassData;
			parentCls->childTypes.emplace_back(cls);

			componentClasses[cls->name] = cls;
		}

		template<IsObjectComponent component, IsAbstractObjectComponent parent>
		void registerClass() {
			registerAbstractClass<component, parent>();
			Class *cls = (Class*) &component::ClassData;
			cls->create = component::create;
		}
	};
}
