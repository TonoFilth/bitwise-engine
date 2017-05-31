set(PROJ_DIR    ${CMAKE_CURRENT_SOURCE_DIR})
set(PUBLIC_DIR  ${PROJ_DIR}/public/bitwise)
set(PRIVATE_DIR ${PROJ_DIR}/private/bitwise)

set(CMAKE_BUILD_TYPE DEBUG)
set(CMAKE_CXX_FLAGS_DEBUG   "${CMAKE_CXX_FLAGS_DEBUG}   -O0 -ggdb")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O2")

include_directories("${PROJ_DIR}/public" "${PROJ_DIR}/private")

# System agnostic headers and sources
file(GLOB_RECURSE HEADERS      "${PUBLIC_DIR}/*.h"    "${PUBLIC_DIR}/*.inl")
file(GLOB_RECURSE SOURCES      "${PRIVATE_DIR}/*.cpp" "${PRIVATE_DIR}/*.cpp")
file(GLOB_RECURSE PRIV_HEADERS "${PRIVATE_DIR}/*.h"   "${PRIVATE_DIR}/*.inl")

# System specific headers and source files
file(GLOB_RECURSE SYS_HEADERS ${PUBLIC_DIR}/platform/${BW_SYSTEM_DIR}/*.h    ${PUBLIC_DIR}/platform/${BW_SYSTEM_DIR}/*.inl ${PRIVATE_DIR}/platform/${BW_SYSTEM_DIR}/*.h)
file(GLOB_RECURSE SYS_SOURCES ${PRIVATE_DIR}/platform/${BW_SYSTEM_DIR}/*.cpp ${PRIVATE_DIR}/platform/${BW_SYSTEM_DIR}/*.mm)

# Unix shared files
if (BW_SYSTEM_UNIX)
    file(GLOB_RECURSE SYS_SHARED_HEADERS "${PUBLIC_DIR}/platform/unix/*.h" "${PUBLIC_DIR}/platform/unix/*.inl")
    file(GLOB_RECURSE SYS_SHARED_SOURCES "${PRIVATE_DIR}/platform/unix/*.cpp")
endif()

# Source groups (for IDEs)
source_group("public"            FILES ${HEADERS})
source_group("public\\platform"  FILES ${SYS_HEADERS})
source_group("public\\platform"  FILES ${SYS_SHARED_HEADERS})
source_group("private"           FILES ${SOURCES})
source_group("private\\platform" FILES ${PRIV_HEADERS})
source_group("private\\platform" FILES ${SYS_SOURCES})
source_group("private\\platform" FILES ${SYS_SHARED_SOURCES})

if (BW_SHARED_LIBS AND NOT THIS_STATIC)
    set(BW_LIB_TYPE SHARED)
    add_definitions(-DBW_EXPORT)
else()
    set(BW_LIB_TYPE STATIC)
    add_definitions(-DBW_STATIC)
endif()

# Generate the static library from the sources
add_library(bitwise ${BW_LIB_TYPE}
    ${HEADERS}
    ${SOURCES}
    ${PRIV_HEADERS}
    ${SYS_HEADERS}
    ${SYS_SOURCES}
    ${SYS_SHARED_HEADERS}
    ${SYS_SHARED_SOURCES})

if (BW_SHARED_LIBS AND NOT THIS_STATIC)
    set_target_properties(bitwise
        PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${BW_BASE_DIR}/bin)
endif()

# Definitions
if (NOT BW_SYSTEM_WINDOWS)
    add_definitions("-std=c++11")
endif()