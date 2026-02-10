#include "ve/cs/interface.hpp"
#include "ve/cs/io/gfx/module.hpp"
#include "ve/cs/io/module.hpp"
#include "ve/io/gfx/graphics_program.hpp"
#include "ve/io/gfx/mesh.hpp"
#include "ve/io/gfx/mesh_provider.hpp"
#include "ve/io/gfx/program_uniform.hpp"
#include "ve/io/gfx/renderer.hpp"
#include "ve/io/gfx/shader.hpp"
#include "ve/io/gfx/shader_source_provider.hpp"
#include "ve/io/gfx/texture.hpp"
#include "ve/io/gfx/texture_provider.hpp"
#include "ve/io/gfx/vertex.hpp"
#include <cstddef>
#include <cstdint>
#include <filesystem>
#include <format>
#include <glm/ext/matrix_float4x4.hpp>
#include <glm/ext/vector_float2.hpp>
#include <glm/ext/vector_float4.hpp>
#include <glm/ext/vector_int2.hpp>
#include <iostream>
#include <memory>
#include <mono-2.0/mono/metadata/appdomain.h>
#include <mono-2.0/mono/metadata/class.h>
#include <mono-2.0/mono/metadata/loader.h>
#include <mono-2.0/mono/metadata/object-forward.h>
#include <mono-2.0/mono/metadata/object.h>
#include <mono-2.0/mono/metadata/exception.h>
#include <vector>

namespace VoidEngine::CS::IO::GFX {
	using namespace VoidEngine::IO::GFX;
	using std::shared_ptr;

	CSharpInterface *interface = nullptr;
	shared_ptr<VoidEngine::IO::GFX::Renderer> renderer = nullptr;

	MonoClass *rendererClass = nullptr;

	// Mesh classes
	MonoClass *vertexClass = nullptr, *meshClass = nullptr, *meshProviderClass = nullptr;

	// Shader classes
	MonoClass *fileShaderSourceProviderClass = nullptr, *shaderSourceProviderClass = nullptr,
			  *shaderClass = nullptr;

	// Texture classes
	MonoClass *textureClass = nullptr, *textureProviderClass = nullptr,
			  *fileTextureProviderClass = nullptr;

	// Program classes
	MonoClass *graphicsProgramClass = nullptr, *uniformClass = nullptr;

	void Renderer_Clear(glm::vec4);
	void Renderer_BindRenderTarget_Window(MonoObject*);
	void Renderer_SwapBuffers(MonoObject*);

	void Mesh_ctor(MonoObject*);
	void Mesh_finalize(MonoObject*);
	MonoArray *Mesh_get_Vertices(MonoObject*);
	MonoArray *Mesh_get_Indices(MonoObject*);
	void Mesh_SetMeshFromProvider(MonoObject*, MonoObject*);

	void FileShaderSourceProvider_ctor(MonoObject*, MonoString*);
	void FileShaderSourceProvider_finalize(MonoObject*);
	MonoString *FileShaderSourceProvider_GetShaderSource(MonoObject*);

	void Shader_ctor(MonoObject*, ShaderType, MonoObject*);
	void Shader_finalize(MonoObject*);

	void GraphicsProgram_ctor(MonoObject*, MonoObject*, MonoObject*);
	void GraphicsProgram_finalize(MonoObject*);
	void GraphicsProgram_Draw(MonoObject*, MonoObject*);
	MonoArray *GraphicsProgram_get_Uniforms(MonoObject*);

	void GraphicsProgram_SetUniform_float(MonoObject *self, MonoObject *target, MonoArray *value);
	void GraphicsProgram_SetUniform_int(MonoObject *self, MonoObject *target, MonoArray *value);
	void GraphicsProgram_SetUniform_vec2(MonoObject *self, MonoObject *target, MonoArray *value);
	void GraphicsProgram_SetUniform_vec3(MonoObject *self, MonoObject *target, MonoArray *value);
	void GraphicsProgram_SetUniform_vec4(MonoObject *self, MonoObject *target, MonoArray *value);
	void GraphicsProgram_SetUniform_ivec2(MonoObject *self, MonoObject *target, MonoArray *value);
	void GraphicsProgram_SetUniform_ivec3(MonoObject *self, MonoObject *target, MonoArray *value);
	void GraphicsProgram_SetUniform_ivec4(MonoObject *self, MonoObject *target, MonoArray *value);
	void GraphicsProgram_SetUniform_mat4(MonoObject *self, MonoObject *target, MonoArray *value);
	void GraphicsProgram_SetUniform_Texture(MonoObject *self, MonoObject *target, MonoArray *value);

	MonoString *Uniform_get_Name(MonoObject*);
	uint32_t Uniform_get_Location(MonoObject*);
	UniformType Uniform_get_Type(MonoObject*);

	void Texture_ctor(MonoObject*, uint8_t);
	void Texture_finalize(MonoObject*);
	bool Texture_get_Filtered(MonoObject*);
	void Texture_set_Filtered(MonoObject*, bool);
	uint8_t Texture_get_TextureSlot(MonoObject*);
	void Texture_Bind(MonoObject*);
	void Texture_SetTextureProvider(MonoObject*, MonoObject*);

	void FileTextureProvider_ctor(MonoObject*, MonoString*);
	void FileTextureProvider_finalize(MonoObject*);
	glm::ivec2 FileTextureProvider_GetSize(MonoObject*);
	MonoArray *FileTextureProvider_GetData(MonoObject*);

	void initModule_Engine_IO_GFX(void) {
		mono_add_internal_call("VoidEngine.IO.GFX.Renderer::Clear", (void*) Renderer_Clear);
		mono_add_internal_call("VoidEngine.IO.GFX.Renderer::BindRenderTarget(VoidEngine.IO.Window)", (void*) Renderer_BindRenderTarget_Window);
		mono_add_internal_call("VoidEngine.IO.GFX.Renderer::SwapBuffers", (void*) Renderer_SwapBuffers);

		mono_add_internal_call("VoidEngine.IO.GFX.Mesh::.ctor", (void*) Mesh_ctor);
		mono_add_internal_call("VoidEngine.IO.GFX.Mesh::Finalize", (void*) Mesh_finalize);
		mono_add_internal_call("VoidEngine.IO.GFX.Mesh::get_Vertices", (void*) Mesh_get_Vertices);
		mono_add_internal_call("VoidEngine.IO.GFX.Mesh::get_Indices", (void*) Mesh_get_Indices);
		mono_add_internal_call("VoidEngine.IO.GFX.Mesh::SetMeshFromProvider", (void*) Mesh_SetMeshFromProvider);

		mono_add_internal_call("VoidEngine.IO.GFX.FileShaderSourceProvider::.ctor", (void*) FileShaderSourceProvider_ctor);
		mono_add_internal_call("VoidEngine.IO.GFX.FileShaderSourceProvider::Finalize", (void*) FileShaderSourceProvider_finalize);
		mono_add_internal_call("VoidEngine.IO.GFX.FileShaderSourceProvider::GetShaderSource", (void*) FileShaderSourceProvider_GetShaderSource);

		mono_add_internal_call("VoidEngine.IO.GFX.Shader::.ctor", (void*) Shader_ctor);
		mono_add_internal_call("VoidEngine.IO.GFX.Shader::Finalize", (void*) Shader_finalize);

		mono_add_internal_call("VoidEngine.IO.GFX.GraphicsProgram::.ctor", (void*) GraphicsProgram_ctor);
		mono_add_internal_call("VoidEngine.IO.GFX.GraphicsProgram::Finalize", (void*) GraphicsProgram_finalize);
		mono_add_internal_call("VoidEngine.IO.GFX.GraphicsProgram::Draw", (void*) GraphicsProgram_Draw);
		mono_add_internal_call("VoidEngine.IO.GFX.GraphicsProgram::get_Uniforms", (void*) GraphicsProgram_get_Uniforms);

		mono_add_internal_call("VoidEngine.IO.GFX.GraphicsProgram::SetUniform(VoidEngine.IO.GFX.Uniform,single[])", (void*) GraphicsProgram_SetUniform_float);
		mono_add_internal_call("VoidEngine.IO.GFX.GraphicsProgram::SetUniform(VoidEngine.IO.GFX.Uniform,int[])", (void*) GraphicsProgram_SetUniform_int);
		mono_add_internal_call("VoidEngine.IO.GFX.GraphicsProgram::SetUniform(VoidEngine.IO.GFX.Uniform,VoidEngine.Math.Vec2f[])", (void*) GraphicsProgram_SetUniform_vec2);
		mono_add_internal_call("VoidEngine.IO.GFX.GraphicsProgram::SetUniform(VoidEngine.IO.GFX.Uniform,VoidEngine.Math.Vec3f[])", (void*) GraphicsProgram_SetUniform_vec3);
		mono_add_internal_call("VoidEngine.IO.GFX.GraphicsProgram::SetUniform(VoidEngine.IO.GFX.Uniform,VoidEngine.Math.Vec4f[])", (void*) GraphicsProgram_SetUniform_vec4);
		mono_add_internal_call("VoidEngine.IO.GFX.GraphicsProgram::SetUniform(VoidEngine.IO.GFX.Uniform,VoidEngine.Math.Vec2i[])", (void*) GraphicsProgram_SetUniform_ivec2);
		mono_add_internal_call("VoidEngine.IO.GFX.GraphicsProgram::SetUniform(VoidEngine.IO.GFX.Uniform,VoidEngine.Math.Vec3i[])", (void*) GraphicsProgram_SetUniform_ivec3);
		mono_add_internal_call("VoidEngine.IO.GFX.GraphicsProgram::SetUniform(VoidEngine.IO.GFX.Uniform,VoidEngine.Math.Vec4i[])", (void*) GraphicsProgram_SetUniform_ivec4);
		mono_add_internal_call("VoidEngine.IO.GFX.GraphicsProgram::SetUniform(VoidEngine.IO.GFX.Uniform,VoidEngine.Math.Mat4x4f[])", (void*) GraphicsProgram_SetUniform_mat4);
		mono_add_internal_call("VoidEngine.IO.GFX.GraphicsProgram::SetUniform(VoidEngine.IO.GFX.Uniform,VoidEngine.IO.GFX.Texture[])", (void*) GraphicsProgram_SetUniform_Texture);

		mono_add_internal_call("VoidEngine.IO.GFX.Uniform::get_Name", (void*) Uniform_get_Name);
		mono_add_internal_call("VoidEngine.IO.GFX.Uniform::get_Location", (void*) Uniform_get_Location);
		mono_add_internal_call("VoidEngine.IO.GFX.Uniform::get_Type", (void*) Uniform_get_Type);

		mono_add_internal_call("VoidEngine.IO.GFX.Texture::.ctor", (void*) Texture_ctor);
		mono_add_internal_call("VoidEngine.IO.GFX.Texture::Finalize", (void*) Texture_finalize);
		mono_add_internal_call("VoidEngine.IO.GFX.Texture::get_Filtered", (void*) Texture_get_Filtered);
		mono_add_internal_call("VoidEngine.IO.GFX.Texture::set_Filtered", (void*) Texture_set_Filtered);
		mono_add_internal_call("VoidEngine.IO.GFX.Texture::get_TextureSlot", (void*) Texture_get_TextureSlot);
		mono_add_internal_call("VoidEngine.IO.GFX.Texture::Bind", (void*) Texture_Bind);
		mono_add_internal_call("VoidEngine.IO.GFX.Texture::SetTextureProvider", (void*) Texture_SetTextureProvider);

		mono_add_internal_call("VoidEngine.IO.GFX.FileTextureProvider::.ctor", (void*) FileTextureProvider_ctor);
		mono_add_internal_call("VoidEngine.IO.GFX.FileTextureProvider::Finalize", (void*) FileTextureProvider_finalize);
		mono_add_internal_call("VoidEngine.IO.GFX.FileTextureProvider::GetData", (void*) FileTextureProvider_GetData);
		mono_add_internal_call("VoidEngine.IO.GFX.FileTextureProvider::GetSize", (void*) FileTextureProvider_GetSize);

		interface = CSharpInterface::getInstance();
		renderer = VoidEngine::IO::GFX::Renderer::getInstance();

		rendererClass = interface->getClass("VoidEngine.IO.GFX", "Renderer");
		vertexClass = interface->getClass("VoidEngine.IO.GFX", "Vertex");
		meshClass = interface->getClass("VoidEngine.IO.GFX", "Mesh");
		meshProviderClass = interface->getClass("VoidEngine.IO.GFX", "AMeshProvider");
		fileShaderSourceProviderClass = interface->getClass("VoidEngine.IO.GFX", "FileShaderSourceProvider");
		shaderSourceProviderClass = interface->getClass("VoidEngine.IO.GFX", "AShaderSourceProvider");
		shaderClass = interface->getClass("VoidEngine.IO.GFX", "Shader");
		graphicsProgramClass = interface->getClass("VoidEngine.IO.GFX", "GraphicsProgram");
		uniformClass = interface->getClass("VoidEngine.IO.GFX", "Uniform");
		textureClass = interface->getClass("VoidEngine.IO.GFX", "Texture");
		textureProviderClass = interface->getClass("VoidEngine.IO.GFX", "ATextureProvider");
		fileTextureProviderClass = interface->getClass("VoidEngine.IO.GFX", "FileTextureProvider");
	}

	MonoClass *getRendererClass(void) { return rendererClass; }
	MonoClass *getVertexClass(void) { return vertexClass; }
	MonoClass *getMeshClass(void) { return meshClass; }
	MonoClass *getMeshProviderClass(void) { return meshProviderClass; }
	MonoClass *getFileShaderSourceProviderClass(void) { return fileShaderSourceProviderClass; }
	MonoClass *getShaderSourceProviderClass(void) { return shaderSourceProviderClass; }
	MonoClass *getShaderClass(void) { return shaderClass; }
	MonoClass *getGraphicsProgramClass(void) { return graphicsProgramClass; }
	MonoClass *getUniformClass(void) { return uniformClass; }
	MonoClass *getTextureClass(void) { return textureClass; }
	MonoClass *getTextureProviderClass(void) { return textureClass; }
	MonoClass *getFileTextureProviderClass(void) { return fileTextureProviderClass; }

	void Renderer_Clear(glm::vec4 color) {
		renderer->clear(color);
	}

	void Renderer_BindRenderTarget_Window(MonoObject *target) {
		if(target == nullptr) {
			mono_raise_exception(mono_get_exception_null_reference());
			return;
		}

		MonoClassField *cxxObject = mono_class_get_field_from_name(VoidEngine::CS::IO::getWindowClass(), "cxxObject");
		shared_ptr<VoidEngine::IO::Window> *window = nullptr;
		mono_field_get_value(target, cxxObject, &window);

		renderer->bindRenderTarget(window->get());
	}
	
	void Renderer_SwapBuffers(MonoObject *windowObj) {
		if(windowObj == nullptr) {
			mono_raise_exception(mono_get_exception_null_reference());
			return;
		}

		MonoClassField *cxxObject = mono_class_get_field_from_name(VoidEngine::CS::IO::getWindowClass(), "cxxObject");
		shared_ptr<VoidEngine::IO::Window> *window = nullptr;
		mono_field_get_value(windowObj, cxxObject, &window);

		renderer->swapBuffers(window->get());
	}

	void Mesh_ctor(MonoObject *self) {
		if(self == nullptr) {
			mono_raise_exception(mono_get_exception_null_reference());
			return;
		} 

		MonoClassField *cxxObject = mono_class_get_field_from_name(meshClass, "cxxObject");
		if(cxxObject == nullptr) throw "";
		
		shared_ptr<VoidEngine::IO::GFX::Mesh> *mesh = new shared_ptr<VoidEngine::IO::GFX::Mesh>(renderer->createMesh());
		mono_field_set_value(self, cxxObject, &mesh);
	}

	void Mesh_finalize(MonoObject *self) {
		if(self == nullptr) {
			mono_raise_exception(mono_get_exception_null_reference());
			return;
		}

		MonoClassField *cxxObject = mono_class_get_field_from_name(meshClass, "cxxObject");
		if(cxxObject == nullptr) throw "";

		shared_ptr<Mesh> *mesh = nullptr;
		mono_field_get_value(self, cxxObject, &mesh);
		if(mesh) delete mesh;
	}

	MonoArray *Mesh_get_Vertices(MonoObject *self) {
		if(self == nullptr) {
			mono_raise_exception(mono_get_exception_null_reference());
			return nullptr;
		}

		MonoClassField *cxxObject = mono_class_get_field_from_name(meshClass, "cxxObject");
		if(cxxObject == nullptr) throw "";

		shared_ptr<Mesh> *mesh = nullptr;
		mono_field_get_value(self, cxxObject, &mesh);

		auto vertices = mesh->get()->getVertexData();
		MonoArray *array = interface->allocArray(vertexClass, vertices.size());
		
		for(size_t idx = 0; idx < vertices.size(); idx++)
			mono_array_set(array, Vertex, idx, vertices[idx]);

		return array;
	}

	MonoArray *Mesh_get_Indices(MonoObject *self) {
		if(self == nullptr) {
			mono_raise_exception(mono_get_exception_null_reference());
			return nullptr;
		}

		MonoClassField *cxxObject = mono_class_get_field_from_name(meshClass, "cxxObject");
		if(cxxObject == nullptr) throw "";

		shared_ptr<Mesh> *mesh = nullptr;
		mono_field_get_value(self, cxxObject, &mesh);

		auto indices = mesh->get()->getIndexData();

		MonoDomain *domain = mono_domain_get();
		MonoArray *array = interface->allocArray(mono_get_int32_class(), indices.size());
		
		for(size_t idx = 0; idx < indices.size(); idx++)
			mono_array_set(array, int32_t, idx, indices[idx]);

		return array;
	}

	void Mesh_SetMeshFromProvider(MonoObject *self, MonoObject *provider) {
		if(self == nullptr || provider == nullptr) {
			mono_raise_exception(mono_get_exception_null_reference());
			return;
		}

		MonoClassField *cxxObject = mono_class_get_field_from_name(meshClass, "cxxObject");
		if(cxxObject == nullptr) throw "";

		shared_ptr<Mesh> *mesh = nullptr;
		mono_field_get_value(self, cxxObject, &mesh);

		MonoClass *customProviderClass = mono_object_get_class(provider);
		if(!mono_class_is_subclass_of(customProviderClass, meshProviderClass, false)) throw "";

		MonoMethod *getVertices = mono_class_get_method_from_name(customProviderClass, "GetVertices", 0);
		MonoMethod *getIndices = mono_class_get_method_from_name(customProviderClass, "GetIndices", 0);

		MonoArray *verticesArr = (MonoArray*) mono_runtime_invoke(getVertices, provider, nullptr, nullptr);
		MonoArray *indicesArr = (MonoArray*) mono_runtime_invoke(getIndices, provider, nullptr, nullptr);

		std::vector<Vertex> vertices(mono_array_length(verticesArr));
		std::vector<uint32_t> indices(mono_array_length(indicesArr));

		for(size_t idx = 0; idx < vertices.size(); idx++) vertices[idx] = mono_array_get(verticesArr, Vertex, idx);
		for(size_t idx = 0; idx < indices.size(); idx++) indices[idx] = mono_array_get(indicesArr, uint32_t, idx);

		BasicMeshProvider meshProvider(vertices, indices);
		mesh->get()->setMeshFromProvider(meshProvider);
	}

	void FileShaderSourceProvider_ctor(MonoObject *self, MonoString *filePath) {
		if(self == nullptr || filePath == nullptr) {
			mono_raise_exception(mono_get_exception_null_reference());
			return;
		}

		std::filesystem::path shaderPath = mono_string_to_utf8(filePath);
		if(!std::filesystem::exists(shaderPath)) {
			mono_raise_exception(mono_get_exception_file_not_found(filePath));
			return;
		}
		
		MonoClassField *cxxObject = mono_class_get_field_from_name(fileShaderSourceProviderClass, "cxxObject");
		if(cxxObject == nullptr) throw "";

		// TODO: Forward thrown exceptions to c#
		FileShaderSourceProvider *provider = new FileShaderSourceProvider(shaderPath);
		mono_field_set_value(self, cxxObject, &provider);
	}

	void FileShaderSourceProvider_finalize(MonoObject *self) {
		if(self == nullptr) {
			mono_raise_exception(mono_get_exception_null_reference());
			return;
		}
		
		MonoClassField *cxxObject = mono_class_get_field_from_name(fileShaderSourceProviderClass, "cxxObject");
		if(cxxObject == nullptr) throw "";

		FileShaderSourceProvider *provider = nullptr;
		mono_field_get_value(self, cxxObject, &provider);
		delete provider;
	}

	MonoString *FileShaderSourceProvider_GetShaderSource(MonoObject *self) {
		if(self == nullptr) {
			mono_raise_exception(mono_get_exception_null_reference());
			return nullptr;
		}

		MonoClassField *cxxObject = mono_class_get_field_from_name(fileShaderSourceProviderClass, "cxxObject");
		if(cxxObject == nullptr) throw "";
		
		FileShaderSourceProvider *provider = nullptr;
		mono_field_get_value(self, cxxObject, &provider);
		auto source = provider->getShaderSource();

		return mono_string_new_wrapper(source.c_str());
	}

	void Shader_ctor(MonoObject *self, ShaderType type, MonoObject *sourceProvider) {
		if(self == nullptr || sourceProvider == nullptr) {
			mono_raise_exception(mono_get_exception_null_reference());
			return;
		}

		MonoClassField *cxxObject = mono_class_get_field_from_name(shaderClass, "cxxObject");
		if(cxxObject == nullptr) throw "";
		
		MonoClass *providerClass = mono_object_get_class(sourceProvider);
		MonoMethod *getMethod = mono_class_get_method_from_name(providerClass, "GetShaderSource", 0);
		MonoString *sourceCode = (MonoString*) mono_runtime_invoke(getMethod, sourceProvider, nullptr, nullptr);

		BasicShaderSourceProvider basicProvider(mono_string_to_utf8(sourceCode));
		shared_ptr<Shader> *shader = new shared_ptr<Shader>(renderer->createShader(type, basicProvider));
		mono_field_set_value(self, cxxObject, &shader);
	}

	void Shader_finalize(MonoObject *self) {
		if(self == nullptr) {
			mono_raise_exception(mono_get_exception_null_reference());
			return;
		}

		MonoClassField *cxxObject = mono_class_get_field_from_name(shaderClass, "cxxObject");
		if(cxxObject == nullptr) throw "";

		shared_ptr<Shader> *shader = nullptr;
		mono_field_get_value(self, cxxObject, &shader);
		delete shader;
	}

	void GraphicsProgram_ctor(MonoObject *self, MonoObject *vertex, MonoObject *fragment) {
		if(self == nullptr || vertex == nullptr || fragment == nullptr) {
			mono_raise_exception(mono_get_exception_null_reference());
			return;
		}

		MonoClassField *shaderCxxObject = mono_class_get_field_from_name(shaderClass, "cxxObject");
		if(shaderCxxObject == nullptr) throw "";

		shared_ptr<Shader> *vertexPtr = nullptr, *fragmentPtr = nullptr;
		mono_field_get_value(vertex, shaderCxxObject, &vertexPtr);
		mono_field_get_value(fragment, shaderCxxObject, &fragmentPtr);

		MonoClassField *cxxObject = mono_class_get_field_from_name(graphicsProgramClass, "cxxObject");
		if(cxxObject == nullptr) throw "";

		shared_ptr<GraphicsProgram> *gfxProgram = new shared_ptr<GraphicsProgram>(renderer->createGraphicsProgram(*vertexPtr, *fragmentPtr));
		mono_field_set_value(self, cxxObject, &gfxProgram);
	}

	void GraphicsProgram_finalize(MonoObject *self) {
		if(self == nullptr) {
			mono_raise_exception(mono_get_exception_null_reference());
			return;
		}

		MonoClassField *cxxObject = mono_class_get_field_from_name(graphicsProgramClass, "cxxObject");
		if(cxxObject == nullptr) throw "";

		shared_ptr<GraphicsProgram> *gfxProgram = nullptr;
		mono_field_get_value(self, cxxObject, &gfxProgram);
		if(gfxProgram) delete gfxProgram;
	}

	void GraphicsProgram_Draw(MonoObject *self, MonoObject *mesh) {
		if(self == nullptr) {
			mono_raise_exception(mono_get_exception_null_reference());
			return;
		}

		MonoClassField *meshCxxObject = mono_class_get_field_from_name(meshClass, "cxxObject");
		if(meshCxxObject == nullptr) throw "";

		MonoClassField *cxxObject = mono_class_get_field_from_name(graphicsProgramClass, "cxxObject");
		if(cxxObject == nullptr) throw "";

		shared_ptr<Mesh> *meshInstance = nullptr;
		mono_field_get_value(mesh, meshCxxObject, &meshInstance);

		shared_ptr<GraphicsProgram> *gfxProgram = nullptr;
		mono_field_get_value(self, cxxObject, &gfxProgram);

		(*gfxProgram)->draw(*meshInstance);
	}

	MonoArray *GraphicsProgram_get_Uniforms(MonoObject *self) {
		if(self == nullptr) {
			mono_raise_exception(mono_get_exception_null_reference());
			return nullptr;
		}

		MonoClassField *cxxObject = mono_class_get_field_from_name(graphicsProgramClass, "cxxObject");
		if(cxxObject == nullptr) throw "";

		shared_ptr<GraphicsProgram> *gfxProgram = nullptr;
		mono_field_get_value(self, cxxObject, &gfxProgram);

		std::vector<Uniform>& uniforms = (*gfxProgram)->getUniforms();
		MonoArray *array = interface->allocArray(uniformClass, uniforms.size());

		MonoClassField *uniformCxxObject = mono_class_get_field_from_name(uniformClass, "cxxObject");
		if(uniformCxxObject == nullptr) throw "";

		for(size_t idx = 0; idx < uniforms.size(); idx++) {
			MonoObject *uniformCSObj = interface->instanceClass(uniformClass);
			Uniform *toPlace = &uniforms[idx];
			mono_field_set_value(uniformCSObj, uniformCxxObject, &toPlace);
			mono_array_set(array, MonoObject*, idx, uniformCSObj);
		}

		return array;
	}

	void GraphicsProgram_SetUniform_float(MonoObject *self, MonoObject *target, MonoArray *value) {
		if(self == nullptr || target == nullptr || value == nullptr) {
			mono_raise_exception(mono_get_exception_null_reference());
			return;
		}
		auto floats = interface->monoArrayToVector<float>(value);

		shared_ptr<GraphicsProgram> *program = nullptr;
		MonoClassField *cxxObject = mono_class_get_field_from_name(graphicsProgramClass, "cxxObject");
		mono_field_get_value(self, cxxObject, &program);

		Uniform *uniform = nullptr;
		MonoClassField *uniformCxxObject = mono_class_get_field_from_name(uniformClass, "cxxObject");
		mono_field_get_value(target, uniformCxxObject, &uniform);

		(*program)->setUniform(*uniform, floats);
	}

	void GraphicsProgram_SetUniform_int(MonoObject *self, MonoObject *target, MonoArray *value) {
		if(self == nullptr || target == nullptr || value == nullptr) {
			mono_raise_exception(mono_get_exception_null_reference());
			return;
		}
		auto ints = interface->monoArrayToVector<int32_t>(value);

		shared_ptr<GraphicsProgram> *program = nullptr;
		MonoClassField *cxxObject = mono_class_get_field_from_name(graphicsProgramClass, "cxxObject");
		mono_field_get_value(self, cxxObject, &program);

		Uniform *uniform = nullptr;
		MonoClassField *uniformCxxObject = mono_class_get_field_from_name(uniformClass, "cxxObject");
		mono_field_get_value(target, uniformCxxObject, &uniform);

		(*program)->setUniform(*uniform, ints);
	}

	void GraphicsProgram_SetUniform_vec2(MonoObject *self, MonoObject *target, MonoArray *value) {
		if(self == nullptr || target == nullptr || value == nullptr) {
			mono_raise_exception(mono_get_exception_null_reference());
			return;
		}
		auto vecs = interface->monoArrayToVector<glm::vec2>(value);

		shared_ptr<GraphicsProgram> *program = nullptr;
		MonoClassField *cxxObject = mono_class_get_field_from_name(graphicsProgramClass, "cxxObject");
		mono_field_get_value(self, cxxObject, &program);

		Uniform *uniform = nullptr;
		MonoClassField *uniformCxxObject = mono_class_get_field_from_name(uniformClass, "cxxObject");
		mono_field_get_value(target, uniformCxxObject, &uniform);

		(*program)->setUniform(*uniform, vecs);
	}

	void GraphicsProgram_SetUniform_vec3(MonoObject *self, MonoObject *target, MonoArray *value) {
		if(self == nullptr || target == nullptr || value == nullptr) {
			mono_raise_exception(mono_get_exception_null_reference());
			return;
		}
		auto vecs = interface->monoArrayToVector<glm::vec3>(value);

		shared_ptr<GraphicsProgram> *program = nullptr;
		MonoClassField *cxxObject = mono_class_get_field_from_name(graphicsProgramClass, "cxxObject");
		mono_field_get_value(self, cxxObject, &program);

		Uniform *uniform = nullptr;
		MonoClassField *uniformCxxObject = mono_class_get_field_from_name(uniformClass, "cxxObject");
		mono_field_get_value(target, uniformCxxObject, &uniform);

		(*program)->setUniform(*uniform, vecs);
	}

	void GraphicsProgram_SetUniform_vec4(MonoObject *self, MonoObject *target, MonoArray *value) {
		if(self == nullptr || target == nullptr || value == nullptr) {
			mono_raise_exception(mono_get_exception_null_reference());
			return;
		}
		auto vecs = interface->monoArrayToVector<glm::vec4>(value);

		shared_ptr<GraphicsProgram> *program = nullptr;
		MonoClassField *cxxObject = mono_class_get_field_from_name(graphicsProgramClass, "cxxObject");
		mono_field_get_value(self, cxxObject, &program);

		Uniform *uniform = nullptr;
		MonoClassField *uniformCxxObject = mono_class_get_field_from_name(uniformClass, "cxxObject");
		mono_field_get_value(target, uniformCxxObject, &uniform);

		(*program)->setUniform(*uniform, vecs);
	}

	void GraphicsProgram_SetUniform_ivec2(MonoObject *self, MonoObject *target, MonoArray *value) {
		if(self == nullptr || target == nullptr || value == nullptr) {
			mono_raise_exception(mono_get_exception_null_reference());
			return;
		}
		auto vecs = interface->monoArrayToVector<glm::ivec2>(value);

		shared_ptr<GraphicsProgram> *program = nullptr;
		MonoClassField *cxxObject = mono_class_get_field_from_name(graphicsProgramClass, "cxxObject");
		mono_field_get_value(self, cxxObject, &program);

		Uniform *uniform = nullptr;
		MonoClassField *uniformCxxObject = mono_class_get_field_from_name(uniformClass, "cxxObject");
		mono_field_get_value(target, uniformCxxObject, &uniform);

		(*program)->setUniform(*uniform, vecs);
	}

	void GraphicsProgram_SetUniform_ivec3(MonoObject *self, MonoObject *target, MonoArray *value) {
		if(self == nullptr || target == nullptr || value == nullptr) {
			mono_raise_exception(mono_get_exception_null_reference());
			return;
		}
		auto vecs = interface->monoArrayToVector<glm::ivec3>(value);

		shared_ptr<GraphicsProgram> *program = nullptr;
		MonoClassField *cxxObject = mono_class_get_field_from_name(graphicsProgramClass, "cxxObject");
		mono_field_get_value(self, cxxObject, &program);

		Uniform *uniform = nullptr;
		MonoClassField *uniformCxxObject = mono_class_get_field_from_name(uniformClass, "cxxObject");
		mono_field_get_value(target, uniformCxxObject, &uniform);

		(*program)->setUniform(*uniform, vecs);
	}

	void GraphicsProgram_SetUniform_ivec4(MonoObject *self, MonoObject *target, MonoArray *value) {
		if(self == nullptr || target == nullptr || value == nullptr) {
			mono_raise_exception(mono_get_exception_null_reference());
			return;
		}
		auto vecs = interface->monoArrayToVector<glm::ivec4>(value);

		shared_ptr<GraphicsProgram> *program = nullptr;
		MonoClassField *cxxObject = mono_class_get_field_from_name(graphicsProgramClass, "cxxObject");
		mono_field_get_value(self, cxxObject, &program);

		Uniform *uniform = nullptr;
		MonoClassField *uniformCxxObject = mono_class_get_field_from_name(uniformClass, "cxxObject");
		mono_field_get_value(target, uniformCxxObject, &uniform);

		(*program)->setUniform(*uniform, vecs);
	}

	void GraphicsProgram_SetUniform_mat4(MonoObject *self, MonoObject *target, MonoArray *value) {
		if(self == nullptr || target == nullptr || value == nullptr) {
			mono_raise_exception(mono_get_exception_null_reference());
			return;
		}
		auto mats = interface->monoArrayToVector<glm::mat4>(value);

		shared_ptr<GraphicsProgram> *program = nullptr;
		MonoClassField *cxxObject = mono_class_get_field_from_name(graphicsProgramClass, "cxxObject");
		mono_field_get_value(self, cxxObject, &program);

		Uniform *uniform = nullptr;
		MonoClassField *uniformCxxObject = mono_class_get_field_from_name(uniformClass, "cxxObject");
		mono_field_get_value(target, uniformCxxObject, &uniform);

		(*program)->setUniform(*uniform, mats);
	}

	void GraphicsProgram_SetUniform_Texture(MonoObject *self, MonoObject *target, MonoArray *value) {
		if(self == nullptr || target == nullptr || value == nullptr) {
			mono_raise_exception(mono_get_exception_null_reference());
			return;
		}
		
		MonoClassField *cxxObject = mono_class_get_field_from_name(graphicsProgramClass, "cxxObject");
		MonoClassField *uniformCxxObject = mono_class_get_field_from_name(uniformClass, "cxxObject");
		MonoClassField *textureCxxObject = mono_class_get_field_from_name(textureClass, "cxxObject");

		shared_ptr<GraphicsProgram> *program = nullptr;
		mono_field_get_value(self, cxxObject, &program);

		Uniform *uniform = nullptr;
		mono_field_get_value(target, uniformCxxObject, &uniform);

		std::vector<shared_ptr<Texture>> uniValues(mono_array_length(value));
		for(size_t idx = 0; idx < mono_array_length(value); idx++) {
			MonoObject *textureObj = mono_array_get(value, MonoObject*, idx);
			shared_ptr<Texture> *texture = nullptr;
			mono_field_get_value(textureObj, textureCxxObject, &texture);
			uniValues[idx] = shared_ptr<Texture>(*texture);
		}

		(*program)->setUniform(*uniform, uniValues);
	}

	MonoString *Uniform_get_Name(MonoObject *self) {
		if(self == nullptr) {
			mono_raise_exception(mono_get_exception_null_reference());
			return nullptr;
		}

		MonoClassField *cxxObject = mono_class_get_field_from_name(uniformClass, "cxxObject");
		if(cxxObject == nullptr) throw "";

		Uniform *uniform = nullptr;
		mono_field_get_value(self, cxxObject, &uniform);

		return mono_string_new_wrapper(uniform->getName().c_str());
	}

	uint32_t Uniform_get_Location(MonoObject *self) {
		if(self == nullptr) {
			mono_raise_exception(mono_get_exception_null_reference());
			return 0;
		}

		MonoClassField *cxxObject = mono_class_get_field_from_name(uniformClass, "cxxObject");
		if(cxxObject == nullptr) throw "";

		Uniform *uniform = nullptr;
		mono_field_get_value(self, cxxObject, &uniform);

		return uniform->getLocation();
	}

	UniformType Uniform_get_Type(MonoObject *self) {
		if(self == nullptr) {
			mono_raise_exception(mono_get_exception_null_reference());
			return UniformType::INVALID;
		}

		MonoClassField *cxxObject = mono_class_get_field_from_name(uniformClass, "cxxObject");
		if(cxxObject == nullptr) throw "";

		Uniform *uniform = nullptr;
		mono_field_get_value(self, cxxObject, &uniform);

		return uniform->getType();
	}

	void Texture_ctor(MonoObject *self, uint8_t slot) {
		if(self == nullptr) {
			mono_raise_exception(mono_get_exception_null_reference());
			return;
		}

		MonoClassField *cxxObject = mono_class_get_field_from_name(textureClass, "cxxObject");
		shared_ptr<Texture> *texture = new shared_ptr<Texture>(renderer->createTexture(slot));
		mono_field_set_value(self, cxxObject, &texture);
	}

	void Texture_finalize(MonoObject *self) {
		if(self == nullptr) {
			mono_raise_exception(mono_get_exception_null_reference());
			return;
		}

		shared_ptr<Texture> *texture = nullptr;
		MonoClassField *cxxObject = mono_class_get_field_from_name(textureClass, "cxxObject");
		mono_field_get_value(self, cxxObject, &texture);
		delete texture;
	}

	bool Texture_get_Filtered(MonoObject *self) {
		if(self == nullptr) {
			mono_raise_exception(mono_get_exception_null_reference());
			return false;
		}

		shared_ptr<Texture> *texture = nullptr;
		MonoClassField *cxxObject = mono_class_get_field_from_name(textureClass, "cxxObject");
		mono_field_get_value(self, cxxObject, &texture);

		return (*texture)->isFiltered();
	}

	void Texture_set_Filtered(MonoObject *self, bool value) {
		if(self == nullptr) {
			mono_raise_exception(mono_get_exception_null_reference());
			return;
		}

		shared_ptr<Texture> *texture = nullptr;
		MonoClassField *cxxObject = mono_class_get_field_from_name(textureClass, "cxxObject");
		mono_field_get_value(self, cxxObject, &texture);

		(*texture)->setFiltered(value);
	}

	uint8_t Texture_get_TextureSlot(MonoObject *self) {
		if(self == nullptr) {
			mono_raise_exception(mono_get_exception_null_reference());
			return -1;
		}

		shared_ptr<Texture> *texture = nullptr;
		MonoClassField *cxxObject = mono_class_get_field_from_name(textureClass, "cxxObject");
		mono_field_get_value(self, cxxObject, &texture);

		return (*texture)->getTextureSlot();
	}

	void Texture_Bind(MonoObject *self) {
		if(self == nullptr) {
			mono_raise_exception(mono_get_exception_null_reference());
			return;
		}

		shared_ptr<Texture> *texture = nullptr;
		MonoClassField *cxxObject = mono_class_get_field_from_name(textureClass, "cxxObject");
		mono_field_get_value(self, cxxObject, &texture);

		(*texture)->bindTexture();
	}

	void Texture_SetTextureProvider(MonoObject *self, MonoObject *provider) {
		if(self == nullptr || provider == nullptr) {
			mono_raise_exception(mono_get_exception_null_reference());
			return;
		}

		shared_ptr<Texture> *texture = nullptr;
		MonoClassField *cxxObject = mono_class_get_field_from_name(textureClass, "cxxObject");
		mono_field_get_value(self, cxxObject, &texture);

		MonoClass *providerClass = mono_object_get_class(provider);
		MonoMethod *providerGetData = mono_class_get_method_from_name(providerClass, "GetData", 0);
		MonoMethod *providerGetSize = mono_class_get_method_from_name(providerClass, "GetSize", 0);

		glm::ivec2 size;
		MonoObject *sizeObj = mono_runtime_invoke(providerGetSize, provider, nullptr, nullptr);
		size = *(glm::ivec2*) mono_object_unbox(sizeObj);

		MonoArray *dataArr = (MonoArray*) mono_runtime_invoke(providerGetData, provider, nullptr, nullptr);
		auto data = interface->monoArrayToVector<uint8_t>(dataArr);

		BasicTextureProvider texProvider(data, size);
		(*texture)->setTextureProvider(texProvider);
	}

	void FileTextureProvider_ctor(MonoObject *self, MonoString *filePath) {
		if(self == nullptr || filePath == nullptr) {
			mono_raise_exception(mono_get_exception_null_reference());
			return;
		}

		std::filesystem::path path = mono_string_to_utf8(filePath);
		FileTextureProvider *provider = new FileTextureProvider(path);
		MonoClassField *cxxObject = mono_class_get_field_from_name(fileTextureProviderClass, "cxxObject");
		mono_field_set_value(self, cxxObject, &provider);
	}

	void FileTextureProvider_finalize(MonoObject *self) {
		if(self == nullptr) {
			mono_raise_exception(mono_get_exception_null_reference());
			return;
		}

		FileTextureProvider *provider = nullptr;
		MonoClassField *cxxObject = mono_class_get_field_from_name(fileTextureProviderClass, "cxxObject");
		mono_field_set_value(self, cxxObject, &provider);
		if(provider) delete provider;
	}

	glm::ivec2 FileTextureProvider_GetSize(MonoObject *self) {
		if(self == nullptr) {
			mono_raise_exception(mono_get_exception_null_reference());
			return { 0, 0 };
		}

		FileTextureProvider *provider = nullptr;
		MonoClassField *cxxObject = mono_class_get_field_from_name(fileTextureProviderClass, "cxxObject");
		mono_field_get_value(self, cxxObject, &provider);

		return provider->getSize();
	}

	MonoArray *FileTextureProvider_GetData(MonoObject *self) {
		if(self == nullptr) {
			mono_raise_exception(mono_get_exception_null_reference());
			return nullptr;
		}

		FileTextureProvider *provider = nullptr;
		MonoClassField *cxxObject = mono_class_get_field_from_name(fileTextureProviderClass, "cxxObject");
		mono_field_get_value(self, cxxObject, &provider);

		auto vec = provider->getData();
		MonoArray *arr = interface->allocArray(mono_get_byte_class(), vec.size());

		for(size_t idx = 0; idx < vec.size(); idx++)
			mono_array_set(arr, uint8_t, idx, vec[idx]);

		return arr;
	}
}

