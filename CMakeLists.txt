cmake_minimum_required(VERSION 2.8.3)

project(BitwiseEngine)

# ===============================================================================
#	Global vars
# ===============================================================================
set(BW_BASE_DIR 	${CMAKE_SOURCE_DIR})
set(BW_CMAKE_DIR	${BW_BASE_DIR}/cmake)
set(BW_MACRO_DIR    ${BW_CMAKE_DIR}/macros)
set(BW_LIB_DIR 		${BW_BASE_DIR}/lib)
set(BW_EXTLIB_DIR   ${BW_BASE_DIR}/extlib)
set(BW_ENGINE_DIR	${BW_BASE_DIR}/engine)
set(BW_SAMPLE_DIR   ${BW_BASE_DIR}/samples)
set(BW_TEST_DIR     ${BW_BASE_DIR}/tests)

#set(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/bin)
set(LIBRARY_OUTPUT_PATH 	${BW_LIB_DIR})

# ===============================================================================
#	Include common macros & system detection
# ===============================================================================
include(${BW_CMAKE_DIR}/System.cmake)
include(${BW_MACRO_DIR}/Common.cmake)

# ===============================================================================
#	Options
# ===============================================================================
if (NOT (BW_SYSTEM_EMSCRIPTEN OR BW_SYSTEM_IOS))
	bw_option(BW_SHARED_LIBS TRUE BOOL "Help str")
else()
	set(BW_SHARED_LIBS FALSE)
endif()

bw_option(BW_BUILD_SAMPLES FALSE BOOL "Build all engine samples")
bw_option(BW_BUILD_TESTS   FALSE BOOL "Build all engine tests")

# ===============================================================================
#   Engine projects
# ===============================================================================
add_subdirectory(${BW_ENGINE_DIR})

# ===============================================================================
#   Sample projects
# ===============================================================================
if (BW_BUILD_SAMPLES)
	add_subdirectory(${BW_SAMPLE_DIR})
endif()

# ===============================================================================
#   Test projects
# ===============================================================================
if (BW_BUILD_TESTS)
	add_subdirectory(${BW_TEST_DIR})
endif()