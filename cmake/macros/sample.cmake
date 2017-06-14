include(CMakeParseArguments)

# ===============================================================================
#   Macro to build samples
# ===============================================================================
macro(sample SAMPLE_NAME)

	set(oneValueArgs GROUP)
	cmake_parse_arguments(THIS "" "${oneValueArgs}" "" ${ARGN})

	string(TOLOWER ${CMAKE_BUILD_TYPE} BUILD_TYPE)

	# Sample directory
	set(SAMPLE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/${SAMPLE_NAME})

	# Sample headers and sources

	file(GLOB_RECURSE HEADERS "${SAMPLE_DIR}/*.h"   "${SAMPLE_DIR}/*.inl")
	file(GLOB_RECURSE SOURCES "${SAMPLE_DIR}/*.cpp" "${SAMPLE_DIR}/*.mm")

	# Definitions
	if (NOT BW_SHARED_LIBS)
		add_definitions(-DBW_STATIC)
	endif()

	if (NOT BW_PLATFORM_WINDOWS)
		add_definitions("-std=c++11")
	endif()

	# Includes
	include_directories("${BW_SRC_DIR}/engine/public")
	include_directories("${SAMPLE_DIR}")
	include_directories("${BW_SRC_DIR}/engine/private")	# Included for testing purposes

	# Executable
	add_executable(${SAMPLE_NAME} ${HEADERS} ${SOURCES})

	# Dependencies
	target_link_libraries(${SAMPLE_NAME} "bitwise")

	# Target properties
	set_target_properties(${SAMPLE_NAME} PROPERTIES
	    RUNTIME_OUTPUT_DIRECTORY         ${BW_BIN_DIR}/${CMAKE_ARCH}/${BUILD_TYPE}
        RUNTIME_OUTPUT_DIRECTORY_DEBUG   ${BW_BIN_DIR}/${CMAKE_ARCH}/${BUILD_TYPE}
        RUNTIME_OUTPUT_DIRECTORY_RELEASE ${BW_BIN_DIR}/${CMAKE_ARCH}/${BUILD_TYPE})

	# Source groups (for IDEs)
	source_group("public"  FILES ${HEADERS})
	source_group("private" FILES ${SOURCES})

endmacro()