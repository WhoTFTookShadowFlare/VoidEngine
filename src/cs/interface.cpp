#include "ve/cs/interface.hpp"

#include "ve/cs/engine_module.hpp"
#include "ve/cs/math/module.hpp"
#include "ve/engine.hpp"
#include <algorithm>
#include <cstdint>
#include <cstdlib>
#include <filesystem>
#include <format>
#include <iostream>
#include <mono-2.0/mono/metadata/class.h>
#include <mono-2.0/mono/metadata/metadata.h>
#include <mono-2.0/mono/metadata/object.h>
#include <mono/metadata/appdomain.h>
#include <mono/metadata/image.h>
#include <mono/metadata/loader.h>
#include <mono/metadata/object-forward.h>
#include <mono/metadata/assembly.h>
#include <mono/jit/jit.h>
#include <mono/metadata/mono-config.h>
#include <string>

namespace VoidEngine::CS {
	CSharpInterface *CSharpInterface::instance = nullptr;

	CSharpInterface::CSharpInterface() {
		mono_config_parse(nullptr);
		domain = mono_jit_init("VoidEngine");
		if(domain == nullptr) {
			std::cerr << "[ERR] Failed to create MonoDomain" << std::endl;
			std::exit(1);
		}

		std::filesystem::path veAPIPath = Engine::getInstance()->getExecutablePath().parent_path() / "VoidEngine.dll";
		if(!std::filesystem::exists(veAPIPath)) {
			std::cerr << std::format("[ERR] Failed to find VoidEngine.dll, make sure it is at {}", veAPIPath.string());
			std::exit(1);
		}

		std::string APIPathStr = veAPIPath.string();
		std::replace(APIPathStr.begin(), APIPathStr.end(), '\\', '/');
		MonoAssembly *veAPI = mono_domain_assembly_open(domain, APIPathStr.c_str());
		if(veAPI == nullptr) {
			std::cerr << "[ERR] Failed to open VoidEngine.dll" << std::endl;
			std::exit(1);
		}

		loadedAssemblies.push_back(veAPI);
	}

	CSharpInterface::~CSharpInterface() {
		mono_jit_cleanup(domain);
	}

	CSharpInterface *CSharpInterface::getInstance() {
		if(instance == nullptr) {
			instance = new CSharpInterface();
			initModule_Engine();
			Math::initModule_Engine_Math();
		}
		return instance;
	}

	MonoAssembly *CSharpInterface::loadAssembly(std::filesystem::path assemblyPath) {
		if(std::filesystem::is_symlink(assemblyPath)) assemblyPath = std::filesystem::canonical(assemblyPath);
		if(!std::filesystem::exists(assemblyPath)) {
			std::cerr << std::format("[ERR] No assembly at {}", assemblyPath.string()) << std::endl;
			return nullptr;
		}

		if (!std::filesystem::is_regular_file(assemblyPath)) {
			std::cerr << std::format("[ERR] {} is not a file", assemblyPath.string()) << std::endl;
			return nullptr;
		}

		std::string assemblyPathStr = assemblyPath.string();
		std::replace(assemblyPathStr.begin(), assemblyPathStr.end(), '\\', '/');
		MonoAssembly *assembly = mono_domain_assembly_open(domain, assemblyPathStr.c_str());
		if(assembly == nullptr) {
			std::cerr << std::format("[ERR] Failed to open assembly {}", assemblyPath.string()) << std::endl;
			return nullptr;
		}

		loadedAssemblies.push_back(assembly);
		MonoImage *image = mono_assembly_get_image(assembly);
		MonoMethod *entryPoint = reinterpret_cast<MonoMethod*>(mono_image_get_entry_point(image));
		if(entryPoint != nullptr) {
			std::filesystem::path exePath = Engine::getInstance()->getExecutablePath();
			char *argv[1];
			argv[0] = (char*) exePath.c_str();
			int retVal = mono_jit_exec(domain, assembly, 1, argv);
		}

		return assembly;
	}

	MonoClass *CSharpInterface::getClass(std::string ns, std::string cls) {
		for(MonoAssembly *ass : loadedAssemblies) {
			MonoImage *image = mono_assembly_get_image(ass);
			if(image == nullptr) continue;
			MonoClass *clsType = mono_class_from_name(image, ns.c_str(), cls.c_str());
			if(clsType == nullptr) continue;
			return clsType;
		}

		std::cerr << std::format("Missing class '{}' from namespace '{}'", cls, ns) << std::endl;
		return nullptr;
	}

	MonoObject *CSharpInterface::instanceClass(MonoClass *cls) {
		MonoObject *obj = mono_object_new(domain, cls);
		if(obj == nullptr) {
			std::cerr << "[ERR] Failed to allocate object" << std::endl;
			return nullptr;
		}

		mono_runtime_object_init(obj);
		return obj;
	}

	MonoArray *CSharpInterface::allocArray(MonoClass *cls, uint32_t len) {
		if(cls == nullptr) {
			std::cerr << "cls is nullptr" << std::endl;
			return nullptr;
		}
		return mono_array_new(this->domain, mono_class_from_mono_type(mono_class_get_type(cls)), len);
	}
}

