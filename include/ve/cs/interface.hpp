#pragma once

#include <filesystem>
#include <mono-2.0/mono/metadata/object-forward.h>
#include <mono-2.0/mono/metadata/object.h>
#include <mono/metadata/image.h>
#include <mono/jit/jit.h>
#include <string>
#include <vector>

namespace VoidEngine::CS {
	class CSharpInterface {
		static CSharpInterface *instance;

		MonoDomain *domain = nullptr;
		std::vector<MonoAssembly*> loadedAssemblies;

		CSharpInterface();
	public:
		static CSharpInterface *getInstance();
		~CSharpInterface();

		MonoAssembly *loadAssembly(std::filesystem::path assemblyPath);

		MonoClass *getClass(std::string ns, std::string cls);
		MonoObject *allocClass(MonoClass *cls);
		MonoObject *instanceClass(MonoClass *cls);
		MonoArray *allocArray(MonoClass *cls, uint32_t len);

		template<typename CxxType>
		constexpr std::vector<CxxType> monoArrayToVector(MonoArray *array) {
			std::vector<CxxType> converted(mono_array_length(array));

			for(size_t idx = 0; idx < mono_array_length(array); idx++)
				converted[idx] = mono_array_get(array, CxxType, idx);

			return converted;
		}
	};
}

