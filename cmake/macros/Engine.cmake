include(CMakeParseArguments)

# ===============================================================================
#   Macro to build engine modules
# ===============================================================================
macro(bw_project PROJECT_NAME)

	cmake_parse_arguments(THIS "" "STATIC" "DEPENDS" ${ARGN})

	string(TOUPPER ${PROJECT_NAME} PROJECT_UPPER_NAME)
	string(TOLOWER ${PROJECT_NAME} PROJECT_LOWER_NAME)

	set(PROJ_DIR ${CMAKE_CURRENT_SOURCE_DIR})
	set(INC_ROOT ${PROJ_DIR}/include)
	set(SRC_ROOT ${PROJ_DIR}/src)

	set(INC_BW   ${INC_ROOT}/Bw)
	set(SRC_BW   ${SRC_ROOT}/Bw)
	set(INC_PROJ ${INC_BW}/${PROJECT_NAME})
	set(SRC_PROJ ${SRC_BW}/${PROJECT_NAME})

	include_directories("${INC_ROOT}" "${SRC_ROOT}")

	# System agnostic headers and sources
	file(GLOB HEADERS      "${INC_BW}/*.h" "${INC_PROJ}/*.h" "${INC_PROJ}/*.inl")
	file(GLOB SOURCES      "${SRC_BW}/*.cpp" "${SRC_PROJ}/*.cpp")
	file(GLOB PRIV_HEADERS "${SRC_PROJ}/*.h" "${SRC_PROJ}/*.inl")

	# System specific headers and source files
	file(GLOB SYS_HEADERS ${INC_PROJ}/${BW_SYSTEM_DIR}/*.h   ${INC_PROJ}/${BW_SYSTEM_DIR}/*.inl ${SRC_PROJ}/${BW_SYSTEM_DIR}/*.h)
	file(GLOB SYS_SOURCES ${SRC_PROJ}/${BW_SYSTEM_DIR}/*.cpp ${SRC_PROJ}/${BW_SYSTEM_DIR}/*.mm)

	# Unix shared files
	if (BW_SYSTEM_UNIX)
		file(GLOB SYS_SHARED_HEADERS "${INC_PROJ}/Unix/*.inl" "${INC_PROJ}/Unix/*.h")
		file(GLOB SYS_SHARED_SOURCES "${SRC_PROJ}/Unix/*.cpp")
	endif()

	# Source groups (for IDEs)
	source_group("include"          FILES ${HEADERS})
	source_group("include\\private" FILES ${PRIV_HEADERS})
	source_group("include\\system"  FILES ${SYS_HEADERS})
	source_group("include\\system"  FILES ${SYS_SHARED_HEADERS})
	source_group("src"              FILES ${SOURCES})
	source_group("src\\system"      FILES ${SYS_SOURCES})
	source_group("src\\system"      FILES ${SYS_SHARED_SOURCES})

	if (BW_SHARED_LIBS AND NOT THIS_STATIC)
		set(BW_LIB_TYPE SHARED)
		add_definitions(-DBW_${PROJECT_UPPER_NAME}_EXPORT)
	else()
		set(BW_LIB_TYPE STATIC)
		add_definitions(-DBW_STATIC_LIB)
	endif()

	# Generate the static library from the sources
	add_library(bw-${PROJECT_LOWER_NAME} ${BW_LIB_TYPE}
		${HEADERS}
		${SOURCES}
		${PRIV_HEADERS}
		${SYS_HEADERS}
		${SYS_SOURCES}
		${SYS_SHARED_HEADERS}
		${SYS_SHARED_SOURCES})

	if (BW_SHARED_LIBS AND NOT THIS_STATIC)
		set_target_properties(bw-${PROJECT_LOWER_NAME}
			PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${BW_BASE_DIR}/bin)
	endif()

	# Include dependency projects
	if (THIS_DEPENDS)
		foreach(DEP ${THIS_DEPENDS})
			string(TOLOWER ${DEP} LOWER_DEP)
			string(TOUPPER ${DEP} UPPER_DEP)

			include_directories("${BW_ENGINE_DIR}/${LOWER_DEP}/include")
			add_definitions(-DBW_${UPPER_DEP}_EXPORT)
			target_link_libraries(bw-${PROJECT_LOWER_NAME} bw-${LOWER_DEP})
		endforeach()
	endif()

	if (NOT BW_SYSTEM_WINDOWS)
		add_definitions("-std=c++11")
	endif()

endmacro()