include(CMakeParseArguments)

# ===============================================================================
#   Macro to get engine module header and source files
# ===============================================================================
macro(engine_module MODULE_NAME HEADERS SOURCES PLATFORM_HEADERS PLATFORM_SOURCES)

	set(MODULE_PUBLIC  "${PUBLIC_DIR}/${MODULE_NAME}")
	set(MODULE_PRIVATE "${PRIVATE_DIR}/${MODULE_NAME}")

	# Module headers and sources
	file(GLOB MODULE_HEADERS "${MODULE_PUBLIC}.h"    "${MODULE_PUBLIC}/*.h" "${MODULE_PUBLIC}/*.inl" "${MODULE_PRIVATE}/*.h" "${MODULE_PRIVATE}/*.inl")
	file(GLOB MODULE_SOURCES "${MODULE_PRIVATE}.cpp" "${MODULE_PRIVATE}/*.cpp" "${MODULE_PRIVATE}/*.mm")

	# Platform headers and sources
	file(GLOB MODULE_PLATFORM_HEADERS "${MODULE_PUBLIC}/platform/${BW_PLATFORM_DIR}/*.h" "${MODULE_PUBLIC}/platform/${BW_PLATFORM_DIR}/*.inl" "${MODULE_PRIVATE}/platform/${BW_PLATFORM_DIR}/*.inl")
	file(GLOB MODULE_PLATFORM_SOURCES "${PRIVATE_DIR}/${MODULE_NAME}/platform/${BW_PLATFORM_DIR}/*.cpp" "${PRIVATE_DIR}/${MODULE_NAME}/platform/${BW_PLATFORM_DIR}/*.mm")

	# Unix shared files
	if (BW_PLATFORM_UNIX)
		file(GLOB_RECURSE SYS_SHARED_HEADERS "${MODULE_PUBLIC}/platform/unix/*.h" "${MODULE_PUBLIC}/platform/unix/*.inl" "${MODULE_PRIVATE}/platform/unix/*.h" "${MODULE_PRIVATE}/platform/unix/*.h")
		file(GLOB_RECURSE SYS_SHARED_SOURCES "${MODULE_PRIVATE}/platform/unix/*.cpp")
	endif()

	# Append module sources to engine sources
	list(APPEND HEADERS ${MODULE_HEADERS})
	list(APPEND SOURCES ${MODULE_SOURCES})
	list(APPEND PLATFORM_HEADERS ${MODULE_PLATFORM_HEADERS})
	list(APPEND PLATFORM_SOURCES ${MODULE_PLATFORM_SOURCES})

endmacro()