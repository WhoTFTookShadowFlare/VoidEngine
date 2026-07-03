#pragma once

#include <memory>
#include <string>
#include <unordered_map>
#include <vector>
#include <functional>
#include <iostream>
#include <cassert>

#include "ve/scene/object_component.hpp"

namespace VoidEngine::Scene {
	struct ComponentClass {
		const char* name;

		const ComponentClass *super;
		std::vector<const ComponentClass*> childTypes;

		std::function<std::shared_ptr<AObjectComponent>()> create;

		bool operator==(ComponentClass RHS) const { return name == RHS.name; }

		bool instanceOf(const ComponentClass* cls) const {
			const ComponentClass *check = this;
			while(check != nullptr) {
				if(cls == check) return true;
				check = check->super;
			}
			return false;
		}

		bool isAbstract() const {
			return create != nullptr;
		}
	};

	class ComponentDB {
	private:
		static std::shared_ptr<ComponentDB> instance;

		std::unordered_map<std::string, const ComponentClass*> componentClasses;

		ComponentDB();
	public:
		static std::shared_ptr<ComponentDB> getInstance();

		const ComponentClass* getClassByName(std::string);

		template<IsAbstractObjectComponent component, IsAbstractObjectComponent parent>
		void registerAbstractClass() {
			ComponentClass *cls = (ComponentClass*) &component::ClassData;
			cls->super = &parent::ClassData;

			ComponentClass *parentCls = (ComponentClass*) &parent::ClassData;
			parentCls->childTypes.emplace_back(cls);
		}

		template<IsObjectComponent component, IsAbstractObjectComponent parent>
		void registerClass() {
			registerAbstractClass<component, parent>();
			ComponentClass *cls = (ComponentClass*) &component::ClassData;
			cls->create = component::create;
		}
	};
}
