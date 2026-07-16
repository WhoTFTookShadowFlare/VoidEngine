option(VE_COMPONENT_GRAPHICS_OPENGL "Enalbe OpenGL support for graphics" ON)

if(${VE_COMPONENT_GRAPHICS_OPENGL})
	include(components/graphics/opengl/CMakeLists.txt)
endif()
