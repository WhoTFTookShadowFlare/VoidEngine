option(VE_COMPONENT_SCRIPTS_LUAU "Enalbe luau support for scripts" ON)

if(${VE_COMPONENT_SCRIPTS_LUAU})
	include(components/scripts/luau/CMakeLists.txt)
endif()
