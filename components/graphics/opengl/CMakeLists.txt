set(OPTION_BUILD_TOOLS OFF)
set(OPTION_BUILD_EXAMPLES OFF)
add_subdirectory(components/graphics/opengl/glbinding)

file(GLOB openglScriptSrc "components/graphics/opengl/*.cpp")
target_sources(VoidEngine PRIVATE ${openglScriptSrc})
target_include_directories(VoidEngine PRIVATE components/graphics/opengl)
target_compile_definitions(VoidEngine PUBLIC COMPONENT_GRAPHICS_OPENGL_ENABLED)

target_link_libraries(VoidEngine PRIVATE glbinding::glbinding glbinding::glbinding-aux)

add_custom_command(TARGET VoidEngine POST_BUILD
	COMMAND ${CMAKE_COMMAND} -E copy_if_different
	$<TARGET_FILE:glbinding::glbinding> ${CMAKE_LIBRARY_OUTPUT_DIRECTORY}
)

add_custom_command(TARGET VoidEngine POST_BUILD
	COMMAND ${CMAKE_COMMAND} -E copy_if_different
	$<TARGET_FILE:glbinding::glbinding-aux> ${CMAKE_LIBRARY_OUTPUT_DIRECTORY}
)
