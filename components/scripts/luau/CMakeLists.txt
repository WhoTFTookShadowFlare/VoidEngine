set(LUAU_BUILD_CLI OFF)
add_subdirectory(luau)
target_include_directories(Luau.Analysis PUBLIC "luau/Analysis/include")

file(GLOB luauScriptSrc "*.cpp")
target_sources(VoidEngine PRIVATE ${luauScriptSrc})

target_include_directories(VoidEngine PRIVATE .)
target_link_libraries(VoidEngine PRIVATE Luau.VM Luau.Compiler)
target_compile_definitions(VoidEngine PUBLIC COMPONENT_SCRIPTS_LUAU_ENABLED)

get_target_property(INCLUDE_DIRS Luau.Analysis INCLUDE_DIRECTORIES)
message(STATUS "Include path for Luau.Analysis: ${INCLUDE_DIRS}")
