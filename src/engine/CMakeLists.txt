# Macros
include(${BW_MACRO_DIR}/engine_module.cmake)
include(${BW_MACRO_DIR}/platform_config.cmake)

set(BUILD_TARGET bitwise)
set(PROJ_DIR     ${CMAKE_CURRENT_SOURCE_DIR})
set(PUBLIC_DIR   ${PROJ_DIR}/public/bitwise)
set(PRIVATE_DIR  ${PROJ_DIR}/private/bitwise)
set(SOURCE_FILES "")

include_directories("${PROJ_DIR}/public" "${PROJ_DIR}/private")

# Engine headers and sources
engine_module("core" SOURCE_FILES)
engine_module("math" SOURCE_FILES)

# Set the library type
if (BW_SHARED_LIBS)
    set(BW_LIB_TYPE SHARED)
    add_definitions(-DBW_EXPORT)
else()
    set(BW_LIB_TYPE STATIC)
    add_definitions(-DBW_STATIC)
endif()

# Engine library target
add_library(${BUILD_TARGET} ${BW_LIB_TYPE} ${SOURCE_FILES})

string(TOLOWER ${CMAKE_BUILD_TYPE} BUILD_TYPE)
string(TOLOWER ${BW_LIB_TYPE}      LIB_TYPE)

set_target_properties(${BUILD_TARGET} PROPERTIES
	ARCHIVE_OUTPUT_DIRECTORY         ${BW_LIB_DIR}/${LIB_TYPE}/${CMAKE_ARCH}/${BUILD_TYPE}
    ARCHIVE_OUTPUT_DIRECTORY_DEBUG   ${BW_LIB_DIR}/${LIB_TYPE}/${CMAKE_ARCH}/${BUILD_TYPE}
    ARCHIVE_OUTPUT_DIRECTORY_RELEASE ${BW_LIB_DIR}/${LIB_TYPE}/${CMAKE_ARCH}/${BUILD_TYPE}
    LIBRARY_OUTPUT_DIRECTORY         ${BW_LIB_DIR}/${LIB_TYPE}/${CMAKE_ARCH}/${BUILD_TYPE}
    LIBRARY_OUTPUT_DIRECTORY_DEBUG   ${BW_LIB_DIR}/${LIB_TYPE}/${CMAKE_ARCH}/${BUILD_TYPE}
    LIBRARY_OUTPUT_DIRECTORY_RELEASE ${BW_LIB_DIR}/${LIB_TYPE}/${CMAKE_ARCH}/${BUILD_TYPE}
    RUNTIME_OUTPUT_DIRECTORY         ${BW_BIN_DIR}/${CMAKE_ARCH}/${BUILD_TYPE}
    RUNTIME_OUTPUT_DIRECTORY_DEBUG   ${BW_BIN_DIR}/${CMAKE_ARCH}/${BUILD_TYPE}
    RUNTIME_OUTPUT_DIRECTORY_RELEASE ${BW_BIN_DIR}/${CMAKE_ARCH}/${BUILD_TYPE}
    DEBUG_POSTFIX "-d")

# Platform configuration
configure_platform(BUILD_TARGET)