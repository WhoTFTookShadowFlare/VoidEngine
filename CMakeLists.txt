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

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

add_subdirectory(extern/SDL3)
add_subdirectory(extern/glbinding)

# execute_process(COMMAND pkg-config --cflags mono-2
# 	OUTPUT_VARIABLE monoInclude
# )
# execute_process(COMMAND pkg-config --libs mono-2
# 	OUTPUT_VARIABLE monoLink
# )

file(GLOB_RECURSE VESource "src/**.cpp")
add_library(VoidEngine STATIC ${VESource})
target_include_directories(VoidEngine PUBLIC
	include
)

# target_compile_options(VoidEngine INTERFACE ${monoInclude})
# target_link_options(VoidEngine INTERFACE ${monoLink})

target_include_directories(VoidEngine PRIVATE
	extern/stb
)
target_link_libraries(VoidEngine PRIVATE
	SDL3
	glbinding::glbinding glbinding::glbinding-aux
)
target_link_libraries(VoidEngine PUBLIC
	glm
)

