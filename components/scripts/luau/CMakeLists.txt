set(LUAU_BUILD_CLI OFF)
add_subdirectory(components/scripts/luau/luau)

file(GLOB luauScriptSrc "components/scripts/luau/*.cpp" "components/scripts/luau/types/*.cpp")
target_sources(VoidEngine PRIVATE ${luauScriptSrc})
target_include_directories(VoidEngine PRIVATE components/scripts/luau)

target_link_libraries(VoidEngine PRIVATE Luau.VM Luau.Compiler)
target_compile_definitions(VoidEngine PUBLIC COMPONENT_SCRIPTS_LUAU_ENABLED)

