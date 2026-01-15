#pragma once

#include <filesystem>
#include <mono-2.0/mono/metadata/object-forward.h>
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
		MonoObject *instanceClass(MonoClass *cls);
		MonoArray *allocArray(MonoClass *cls, uint32_t len);
	};
}

