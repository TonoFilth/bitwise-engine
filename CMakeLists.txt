cmake_minimum_required(VERSION 2.8.3)

project(BitwiseEngine)

# ===============================================================================
#   Global vars
# ===============================================================================
set(BW_BASE_DIR         ${CMAKE_SOURCE_DIR})
set(BW_CMAKE_DIR        ${BW_BASE_DIR}/cmake)
set(BW_MACRO_DIR        ${BW_CMAKE_DIR}/macros)
set(BW_BIN_DIR          ${BW_BASE_DIR}/bin)
set(BW_LIB_DIR          ${BW_BASE_DIR}/lib)
set(BW_EXTLIB_DIR       ${BW_BASE_DIR}/extlib)
set(BW_SRC_DIR          ${BW_BASE_DIR}/src)
set(LIBRARY_OUTPUT_PATH ${BW_LIB_DIR})

# ===============================================================================
#   Include common macros & platform detection
# ===============================================================================
include(${BW_CMAKE_DIR}/platform.cmake)
include(${BW_MACRO_DIR}/common.cmake)

# ===============================================================================
#   Options
# ===============================================================================
if (NOT (BW_SYSTEM_EMSCRIPTEN OR BW_SYSTEM_IOS))
    bw_option(BW_SHARED_LIBS TRUE BOOL "Engine library format")
else()
    set(BW_SHARED_LIBS FALSE)
endif()

bw_option(BW_BUILD_SAMPLES FALSE BOOL "Build all engine samples")

# ===============================================================================
#   Source
# ===============================================================================
add_subdirectory(${BW_SRC_DIR})

# ===============================================================================
#   Samples
# ===============================================================================
if (BW_BUILD_SAMPLES)
    set(BW_SAMPLE_DIR     ${BW_BASE_DIR}/samples)
    set(BW_SAMPLE_OUT_DIR ${BW_OUT_DIR}/samples)

    add_subdirectory(${BW_SAMPLE_DIR})
endif()