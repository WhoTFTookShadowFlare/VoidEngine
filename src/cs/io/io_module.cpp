#include "ve/cs/interface.hpp"
#include "ve/cs/io/module.hpp"
#include "ve/io/window.hpp"
#include <format>
#include <glm/ext/vector_int2.hpp>
#include <iostream>
#include <memory>
#include <mono-2.0/mono/metadata/class.h>
#include <mono-2.0/mono/metadata/exception.h>
#include <mono-2.0/mono/metadata/loader.h>
#include <mono-2.0/mono/metadata/object-forward.h>
#include <mono-2.0/mono/metadata/object.h>

namespace VoidEngine::CS::IO {
	using namespace VoidEngine::IO;
	using std::shared_ptr;
	CSharpInterface *interface = nullptr;

	MonoClass *windowCreationOptionsClass = nullptr, *windowClass = nullptr;

	void WindowCreationOptions_ctor(MonoObject*);
	void WindowCreationOptions_finalize(MonoObject*);
	void WindowCreationOptions_set_Size(MonoObject*, glm::ivec2);
	glm::ivec2 WindowCreationOptions_get_Size(MonoObject*);
	void WindowCreationOptions_set_Title(MonoObject*, MonoString*);
	MonoString *WindowCreationOptions_get_Title(MonoObject*);
	void WindowCreationOptions_set_Resizable(MonoObject*, bool);
	bool WindowCreationOptions_get_Resizable(MonoObject*);
	void WindowCreationOptions_set_Borderless(MonoObject*, bool);
	bool WindowCreationOptions_get_Borderless(MonoObject*);
	void WindowCreationOptions_set_AlwaysOnTop(MonoObject*, bool);
	bool WindowCreationOptions_get_AlwaysOnTop(MonoObject*);
	void WindowCreationOptions_set_Utility(MonoObject*, bool);
	bool WindowCreationOptions_get_Utility(MonoObject*);

	void Window_ctor(MonoObject*, MonoObject*);
	void Window_finalize(MonoObject*);
	void Window_set_Size(MonoObject*, glm::ivec2);
	glm::ivec2 Window_get_Size(MonoObject*);
	void Window_set_Position(MonoObject*, glm::ivec2);
	glm::ivec2 Window_get_Position(MonoObject*);
	void Window_set_Title(MonoObject*, MonoString*);
	MonoString *Window_get_Title(MonoObject*);


	void initModule_Engine_IO(void) {
		mono_add_internal_call("VoidEngine.IO.WindowCreationOptions::.ctor", (void*) WindowCreationOptions_ctor);
		mono_add_internal_call("VoidEngine.IO.WindowCreationOptions::Finalize", (void*) WindowCreationOptions_finalize);
		mono_add_internal_call("VoidEngine.IO.WindowCreationOptions::set_Size", (void*) WindowCreationOptions_set_Size);
		mono_add_internal_call("VoidEngine.IO.WindowCreationOptions::get_Size", (void*) WindowCreationOptions_get_Size);
		mono_add_internal_call("VoidEngine.IO.WindowCreationOptions::set_Title", (void*) WindowCreationOptions_set_Title);
		mono_add_internal_call("VoidEngine.IO.WindowCreationOptions::get_Title", (void*) WindowCreationOptions_get_Title);
		mono_add_internal_call("VoidEngine.IO.WindowCreationOptions::set_Resizable", (void*) WindowCreationOptions_set_Resizable);
		mono_add_internal_call("VoidEngine.IO.WindowCreationOptions::get_Resizable", (void*) WindowCreationOptions_get_Resizable);
		mono_add_internal_call("VoidEngine.IO.WindowCreationOptions::set_Borderless", (void*) WindowCreationOptions_set_Borderless);
		mono_add_internal_call("VoidEngine.IO.WindowCreationOptions::get_Borderless", (void*) WindowCreationOptions_get_Borderless);
		mono_add_internal_call("VoidEngine.IO.WindowCreationOptions::set_AlwaysOnTop", (void*) WindowCreationOptions_set_AlwaysOnTop);
		mono_add_internal_call("VoidEngine.IO.WindowCreationOptions::get_AlwaysOnTop", (void*) WindowCreationOptions_get_AlwaysOnTop);
		mono_add_internal_call("VoidEngine.IO.WindowCreationOptions::set_Utility", (void*) WindowCreationOptions_set_Utility);
		mono_add_internal_call("VoidEngine.IO.WindowCreationOptions::get_Utility", (void*) WindowCreationOptions_get_Utility);

		mono_add_internal_call("VoidEngine.IO.Window::.ctor", (void*) Window_ctor);
		mono_add_internal_call("VoidEngine.IO.Window::Finalize", (void*) Window_finalize);
		mono_add_internal_call("VoidEngine.IO.Window::set_Size", (void*) Window_set_Size);
		mono_add_internal_call("VoidEngine.IO.Window::get_Size", (void*) Window_get_Size);
		mono_add_internal_call("VoidEngine.IO.Window::set_Position", (void*) Window_set_Position);
		mono_add_internal_call("VoidEngine.IO.Window::get_Position", (void*) Window_get_Position);
		mono_add_internal_call("VoidEngine.IO.Window::set_Title", (void*) Window_set_Title);
		mono_add_internal_call("VoidEngine.IO.Window::get_Title", (void*) Window_get_Title);

		interface = CSharpInterface::getInstance();

		windowCreationOptionsClass = interface->getClass("VoidEngine.IO", "WindowCreationOptions");
		windowClass = interface->getClass("VoidEngine.IO", "Window");
	}

	MonoClass *getWindowCreationOptionsClass(void) { return windowCreationOptionsClass; }
	MonoClass *getWindowClass(void) { return windowClass; }

	void WindowCreationOptions_ctor(MonoObject *self) {
		if(self == nullptr) {
			mono_raise_exception(mono_get_exception_null_reference());
			return;
		}

		MonoClassField *cxxObject = mono_class_get_field_from_name(windowCreationOptionsClass, "cxxObject");
		Window::CreationOptions *opts = new Window::CreationOptions;
		mono_field_set_value(self, cxxObject, &opts);
		std::cout << opts << std::endl;
	}

	void WindowCreationOptions_finalize(MonoObject *self) {
		if(self == nullptr) {
			mono_raise_exception(mono_get_exception_null_reference());
			return;
		}

		MonoClassField *cxxObject = mono_class_get_field_from_name(windowCreationOptionsClass, "cxxObject");
		Window::CreationOptions *opts = nullptr;
		mono_field_get_value(self, cxxObject, &opts);
		if(opts) delete opts;
	}

	void WindowCreationOptions_set_Size(MonoObject *self, glm::ivec2 value) {
		if(self == nullptr) {
			mono_raise_exception(mono_get_exception_null_reference());
			return;
		}

		MonoClassField *cxxObject = mono_class_get_field_from_name(windowCreationOptionsClass, "cxxObject");
		Window::CreationOptions *opts = nullptr;
		mono_field_get_value(self, cxxObject, &opts);
		std::cout << opts << std::endl;
		opts->size = value;
	}

	glm::ivec2 WindowCreationOptions_get_Size(MonoObject *self) {
		if(self == nullptr) {
			mono_raise_exception(mono_get_exception_null_reference());
			return { 0, 0 };
		}

		MonoClassField *cxxObject = mono_class_get_field_from_name(windowCreationOptionsClass, "cxxObject");
		Window::CreationOptions *opts = nullptr;
		mono_field_get_value(self, cxxObject, &opts);
		return opts->size;
	}

	void WindowCreationOptions_set_Title(MonoObject *self, MonoString *value) {
		if(self == nullptr) {
			mono_raise_exception(mono_get_exception_null_reference());
			return;
		}

		MonoClassField *cxxObject = mono_class_get_field_from_name(windowCreationOptionsClass, "cxxObject");
		Window::CreationOptions *opts = nullptr;
		mono_field_get_value(self, cxxObject, &opts);
		opts->title = mono_string_to_utf8(value);
	}

	MonoString *WindowCreationOptions_get_Title(MonoObject *self) {
		if(self == nullptr) {
			mono_raise_exception(mono_get_exception_null_reference());
			return nullptr;
		}

		MonoClassField *cxxObject = mono_class_get_field_from_name(windowCreationOptionsClass, "cxxObject");
		Window::CreationOptions *opts = nullptr;
		mono_field_get_value(self, cxxObject, &opts);
		return mono_string_new_wrapper(opts->title.c_str());
	}

	void WindowCreationOptions_set_Resizable(MonoObject *self, bool value) {
		if(self == nullptr) {
			mono_raise_exception(mono_get_exception_null_reference());
			return;
		}

		MonoClassField *cxxObject = mono_class_get_field_from_name(windowCreationOptionsClass, "cxxObject");
		Window::CreationOptions *opts = nullptr;
		mono_field_get_value(self, cxxObject, &opts);
		opts->resizable = value;
	}

	bool WindowCreationOptions_get_Resizable(MonoObject *self) {
		if(self == nullptr) {
			mono_raise_exception(mono_get_exception_null_reference());
			return false;
		}

		MonoClassField *cxxObject = mono_class_get_field_from_name(windowCreationOptionsClass, "cxxObject");
		Window::CreationOptions *opts = nullptr;
		mono_field_get_value(self, cxxObject, &opts);
		return opts->resizable;
	}

	void WindowCreationOptions_set_Borderless(MonoObject *self, bool value) {
		if(self == nullptr) {
			mono_raise_exception(mono_get_exception_null_reference());
			return;
		}

		MonoClassField *cxxObject = mono_class_get_field_from_name(windowCreationOptionsClass, "cxxObject");
		Window::CreationOptions *opts = nullptr;
		mono_field_get_value(self, cxxObject, &opts);
		opts->borderless = value;
	}

	bool WindowCreationOptions_get_Borderless(MonoObject *self) {
		if(self == nullptr) {
			mono_raise_exception(mono_get_exception_null_reference());
			return false;
		}

		MonoClassField *cxxObject = mono_class_get_field_from_name(windowCreationOptionsClass, "cxxObject");
		Window::CreationOptions *opts = nullptr;
		mono_field_get_value(self, cxxObject, &opts);
		return opts->borderless;
	}

	void WindowCreationOptions_set_AlwaysOnTop(MonoObject *self, bool value) {
		if(self == nullptr) {
			mono_raise_exception(mono_get_exception_null_reference());
			return;
		}

		MonoClassField *cxxObject = mono_class_get_field_from_name(windowCreationOptionsClass, "cxxObject");
		Window::CreationOptions *opts = nullptr;
		mono_field_get_value(self, cxxObject, &opts);
		opts->alwaysOnTop = value;
	}

	bool WindowCreationOptions_get_AlwaysOnTop(MonoObject *self) {
		if(self == nullptr) {
			mono_raise_exception(mono_get_exception_null_reference());
			return false;
		}

		MonoClassField *cxxObject = mono_class_get_field_from_name(windowCreationOptionsClass, "cxxObject");
		Window::CreationOptions *opts = nullptr;
		mono_field_get_value(self, cxxObject, &opts);
		return opts->alwaysOnTop;
	}

	void WindowCreationOptions_set_Utility(MonoObject *self, bool value) {
		if(self == nullptr) {
			mono_raise_exception(mono_get_exception_null_reference());
			return;
		}

		MonoClassField *cxxObject = mono_class_get_field_from_name(windowCreationOptionsClass, "cxxObject");
		Window::CreationOptions *opts = nullptr;
		mono_field_get_value(self, cxxObject, &opts);
		opts->utility = value;
	}

	bool WindowCreationOptions_get_Utility(MonoObject *self) {
		if(self == nullptr) {
			mono_raise_exception(mono_get_exception_null_reference());
			return false;
		}

		MonoClassField *cxxObject = mono_class_get_field_from_name(windowCreationOptionsClass, "cxxObject");
		Window::CreationOptions *opts = nullptr;
		mono_field_get_value(self, cxxObject, &opts);
		return opts->utility;
	}

	void Window_ctor(MonoObject *self, MonoObject *opts) {
		if(self == nullptr || opts == nullptr) {
			mono_raise_exception(mono_get_exception_null_reference());
			return;
		}
		
		MonoClassField *optsCxxObject = mono_class_get_field_from_name(windowCreationOptionsClass, "cxxObject");
		Window::CreationOptions *cxxOpts = nullptr;
		mono_field_get_value(opts, optsCxxObject, &cxxOpts);

		MonoClassField *cxxObject = mono_class_get_field_from_name(windowClass, "cxxObject");
		shared_ptr<Window> *winPtr = new shared_ptr<Window>(Window::create(*cxxOpts));
		mono_field_set_value(self, cxxObject, &winPtr);
	}

	void Window_finalize(MonoObject *self) {
		if(self == nullptr) {
			mono_raise_exception(mono_get_exception_null_reference());
			return;
		}

		MonoClassField *cxxObject = mono_class_get_field_from_name(windowClass, "cxxObject");
		shared_ptr<Window> *window = nullptr;
		mono_field_get_value(self, cxxObject, &cxxObject);
		delete window;
	}

	void Window_set_Size(MonoObject *self, glm::ivec2 value) {
		if(self == nullptr) {
			mono_raise_exception(mono_get_exception_null_reference());
			return;
		}

		MonoClassField *cxxObject = mono_class_get_field_from_name(windowClass, "cxxObject");
		shared_ptr<Window> *window = nullptr;
		mono_field_get_value(self, cxxObject, &cxxObject);
		(*window)->setSize(value);
	}

	glm::ivec2 Window_get_Size(MonoObject *self) {
		if(self == nullptr) {
			mono_raise_exception(mono_get_exception_null_reference());
			return { 0, 0 };
		}

		MonoClassField *cxxObject = mono_class_get_field_from_name(windowClass, "cxxObject");
		shared_ptr<Window> *window = nullptr;
		mono_field_get_value(self, cxxObject, &cxxObject);
		return (*window)->getSize();
	}

	void Window_set_Position(MonoObject *self, glm::ivec2 value) {
		if(self == nullptr) {
			mono_raise_exception(mono_get_exception_null_reference());
			return;
		}

		MonoClassField *cxxObject = mono_class_get_field_from_name(windowClass, "cxxObject");
		shared_ptr<Window> *window = nullptr;
		mono_field_get_value(self, cxxObject, &cxxObject);
		(*window)->setPosition(value);
	}

	glm::ivec2 Window_get_Position(MonoObject *self) {
		if(self == nullptr) {
			mono_raise_exception(mono_get_exception_null_reference());
			return { 0, 0 };
		}

		MonoClassField *cxxObject = mono_class_get_field_from_name(windowClass, "cxxObject");
		shared_ptr<Window> *window = nullptr;
		mono_field_get_value(self, cxxObject, &cxxObject);
		return (*window)->getPosition();
	}

	void Window_set_Title(MonoObject *self, MonoString *value){
		if(self == nullptr) {
			mono_raise_exception(mono_get_exception_null_reference());
			return;
		}

		MonoClassField *cxxObject = mono_class_get_field_from_name(windowClass, "cxxObject");
		shared_ptr<Window> *window = nullptr;
		mono_field_get_value(self, cxxObject, &cxxObject);
		(*window)->setTitle(mono_string_to_utf8(value));
	}

	MonoString *Window_get_Title(MonoObject *self) {
		if(self == nullptr) {
			mono_raise_exception(mono_get_exception_null_reference());
			return nullptr;
		}

		MonoClassField *cxxObject = mono_class_get_field_from_name(windowClass, "cxxObject");
		shared_ptr<Window> *window = nullptr;
		mono_field_get_value(self, cxxObject, &cxxObject);
		return mono_string_new_wrapper((*window)->getTitle().c_str());
	}
}

