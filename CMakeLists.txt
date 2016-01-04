cmake_minimum_required(VERSION 2.8.3)

project(BitwiseEngine)

# ===============================================================================
#	Global vars
# ===============================================================================
set(BW_BASE_DIR 	${CMAKE_SOURCE_DIR})
set(BW_CMAKE_DIR	${BW_BASE_DIR}/cmake)
set(BW_LIB_DIR 		${BW_BASE_DIR}/lib)
set(BW_ENGINE_DIR	${BW_BASE_DIR}/engine)
set(BW_SAMPLE_DIR   ${BW_BASE_DIR}/samples)

#set(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/bin)
set(LIBRARY_OUTPUT_PATH 	${BW_LIB_DIR})

# ===============================================================================
#	Macros & other stuff
# ===============================================================================
include(${BW_CMAKE_DIR}/Config.cmake)
include(${BW_CMAKE_DIR}/Macros.cmake)

# ===============================================================================
#	Options
# ===============================================================================
if (NOT BW_SYSTEM_EMSCRIPTEN)
	bw_option(BW_SHARED_LIBS TRUE BOOL "Help str")
else()
	set(BW_SHARED_LIBS FALSE)
endif()
bw_option(BW_BUILD_SAMPLES FALSE BOOL "Build all engine samples")

add_subdirectory(${BW_ENGINE_DIR})

if (BW_BUILD_SAMPLES)
	add_subdirectory(${BW_SAMPLE_DIR})
endif()