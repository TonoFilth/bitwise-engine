include(${BW_MACRO_DIR}/Engine.cmake)

# Include all sub-projects
add_subdirectory(${BW_ENGINE_DIR}/base)
add_subdirectory(${BW_ENGINE_DIR}/memory)
add_subdirectory(${BW_ENGINE_DIR}/collections)

if (NOT BW_SYSTEM_EMSCRIPTEN)
	add_subdirectory(${BW_ENGINE_DIR}/main)
endif()