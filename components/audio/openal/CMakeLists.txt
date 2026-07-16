add_subdirectory(components/audio/openal/openal)

file(GLOB openglScriptSrc "components/audio/openal/*.cpp")
target_sources(VoidEngine PRIVATE openalAudioSrc)
target_include_directories(VoidEngine PRIVATE components/audio/openal)
target_compile_definitions(VoidEngine PUBLIC COMPONENT_AUDIO_OPENAL_ENABLED)

target_link_libraries(VoidEngine PRIVATE OpenAL::OpenAL)
