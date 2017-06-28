set(APP_NAME "router")
set(APP_SRC "${BW_APPS_SRC_DIR}/router")

# Source files
set(SOURCE_FILES
	${APP_SRC}/main.cpp
)

# Definitions
if (NOT BW_PLATFORM_WINDOWS)
	add_definitions("-std=c++11")
endif()

# Includes
include_directories("${BW_SRC_DIR}/engine/public")
include_directories("${BW_SRC_DIR}/engine/private")
include_directories("${BW_EXTLIB_DIR}/include/")
include_directories("${APP_SRC}")

# Executable
add_executable(${APP_NAME} ${SOURCE_FILES})

# Dependencies
target_link_libraries(${APP_NAME} "bitwise")

# Target properties
set_target_properties(${APP_NAME} PROPERTIES
	RUNTIME_OUTPUT_DIRECTORY         "${BW_BIN_DIR}/${BW_ARCH}/${BW_BUILD_TYPE}"
    RUNTIME_OUTPUT_DIRECTORY_DEBUG   "${BW_BIN_DIR}/${BW_ARCH}/${BW_BUILD_TYPE}"
    RUNTIME_OUTPUT_DIRECTORY_RELEASE "${BW_BIN_DIR}/${BW_ARCH}/${BW_BUILD_TYPE}")