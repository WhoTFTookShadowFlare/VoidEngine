cmake_minimum_required(VERSION 3.15)
project(VoidEngine
	VERSION 1.0.0
	LANGUAGES CXX
)

find_package(Git QUIET)
if(GIT_FOUND AND EXISTS ${PROJECT_SOURCE_DIR}/bin)
	execute_process(
		COMMAND ${GIT_EXECUTABLE} submodule update --init --recursive
		WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
		RESULT_VARIABLE GIT_SUBMODE_RESULT
	)

	if(NOT GIT_SUBMODE_RESULT EQUAL "0")
		message(FATAL_ERROR "Failed to update submodules!")
	endif()
endif()

if(NOT EXISTS ${PROJECT_SOURCE_DIR}/extern/SDL3/CMakeLists.txt)
	message(FATAL_ERROR "Missing submodule SDL3")
endif()
if(NOT EXISTS ${PROJECT_SOURCE_DIR}/extern/glbinding/CMakeLists.txt)
	message(FATAL_ERROR "Missing submodule glbinding")
endif()
if(NOT EXISTS ${PROJECT_SOURCE_DIR}/extern/glm/CMakeLists.txt)
	message(FATAL_ERROR "Missing submodule glm")
endif()
if(NOT EXISTS ${PROJECT_SOURCE_DIR}/extern/stb)
	message(FATAL_ERROR "Missing submodule stb")
endif()
if(NOT EXISTS ${PROJECT_SOURCE_DIR}/extern/assimp)
	message(FATAL_ERROR "Missing submodule assimp")
endif()

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY $<1:${CMAKE_BINARY_DIR}/bin>)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY $<1:${CMAKE_BINARY_DIR}/bin>)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY $<1:${CMAKE_BINARY_DIR}/lib>)

add_subdirectory(extern/SDL3)

set(OPTION_BUILD_TOOLS OFF)
set(OPTION_BUILD_EXAMPLES OFF)
add_subdirectory(extern/glbinding)

add_subdirectory(extern/assimp)

file(GLOB_RECURSE VESource "src/**.cpp")
add_library(VoidEngine STATIC ${VESource})
target_include_directories(VoidEngine PUBLIC
	include
)

target_include_directories(VoidEngine PRIVATE
	extern/stb
)
target_link_libraries(VoidEngine PRIVATE
	SDL3::SDL3
	glbinding::glbinding glbinding::glbinding-aux
	assimp::assimp
)
target_include_directories(VoidEngine PUBLIC
	extern/SDL3/include
)
target_compile_definitions(VoidEngine PUBLIC GLM_ENABLE_EXPERIMENTAL)
target_include_directories(VoidEngine PUBLIC
	extern/glm
)

add_custom_command(TARGET VoidEngine POST_BUILD
	COMMAND ${CMAKE_COMMAND} -E copy_if_different
	$<TARGET_FILE:glbinding::glbinding> ${CMAKE_LIBRARY_OUTPUT_DIRECTORY}
)

add_custom_command(TARGET VoidEngine POST_BUILD
	COMMAND ${CMAKE_COMMAND} -E copy_if_different
	$<TARGET_FILE:glbinding::glbinding-aux> ${CMAKE_LIBRARY_OUTPUT_DIRECTORY}
)
