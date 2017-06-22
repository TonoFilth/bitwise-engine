set(EXE_NAME "memory_tests")
set(MEMORY_TESTS_SRC "${BW_TESTS_SRC_DIR}/engine/memory")

# Source files
set(SOURCE_FILES
	${MEMORY_TESTS_SRC}/main.cpp
	${MEMORY_TESTS_SRC}/page_allocator.cpp
)

# Definitions
if (NOT BW_SHARED_LIBS)
	add_definitions(-DBW_STATIC)
endif()

if (NOT BW_PLATFORM_WINDOWS)
	add_definitions("-std=c++11")
endif()

# Includes
include_directories("${BW_SRC_DIR}/engine/public")
include_directories("${BW_SRC_DIR}/engine/private")
include_directories("${BW_EXTLIB_DIR}/include/")
include_directories("${MEMORY_TESTS_SRC}")

# Executable
add_executable(${EXE_NAME} ${SOURCE_FILES})

# Dependencies
target_link_libraries(${EXE_NAME} "bitwise")

# Target properties
set_target_properties(${EXE_NAME} PROPERTIES
	RUNTIME_OUTPUT_DIRECTORY         "${BW_BIN_DIR}/${BW_ARCH}/${BW_BUILD_TYPE}"
    RUNTIME_OUTPUT_DIRECTORY_DEBUG   "${BW_BIN_DIR}/${BW_ARCH}/${BW_BUILD_TYPE}"
    RUNTIME_OUTPUT_DIRECTORY_RELEASE "${BW_BIN_DIR}/${BW_ARCH}/${BW_BUILD_TYPE}")