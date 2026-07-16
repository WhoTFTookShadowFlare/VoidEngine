option(VE_COMPONENT_AUDIO_OPENAL "Enalbe OpenAL support for audio" ON)

if(${VE_COMPONENT_AUDIO_OPENAL})
	include(components/audio/openal/CMakeLists.txt)
endif()
