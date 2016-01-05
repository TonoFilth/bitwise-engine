include(CMakeParseArguments)

# ===============================================================================
#   Macro to help define options
# ===============================================================================
macro(bw_option var default type helpstr)
    if(NOT DEFINED ${var})
        set(${var} ${default})
    endif()
    set(${var} ${${var}} CACHE ${type} ${helpstr} FORCE)
endmacro()

# ===============================================================================
#   Macro to build engine library projects
# ===============================================================================
macro(bw_project PROJECT_NAME)

	cmake_parse_arguments(THIS "" "" "DEPENDS" ${ARGN})

	string(TOUPPER ${PROJECT_NAME} PROJECT_UPPER_NAME)
	string(TOLOWER ${PROJECT_NAME} PROJECT_LOWER_NAME)

	set(PROJ_DIR ${CMAKE_CURRENT_SOURCE_DIR}/${PROJECT_LOWER_NAME})
	set(INC_ROOT ${CMAKE_CURRENT_SOURCE_DIR}/${PROJECT_LOWER_NAME}/include)
	set(SRC_ROOT ${CMAKE_CURRENT_SOURCE_DIR}/${PROJECT_LOWER_NAME}/src)

	set(INC_BW   ${INC_ROOT}/Bw)
	set(SRC_BW   ${SRC_ROOT}/Bw)
	set(INC_PROJ ${INC_BW}/${PROJECT_NAME})
	set(SRC_PROJ ${SRC_BW}/${PROJECT_NAME})

	include_directories("${INC_ROOT}" "${SRC_ROOT}")

	# Include dependency projects
	if (THIS_DEPENDS)
		foreach(DEP ${THIS_DEPENDS})
			string(TOLOWER ${DEP} LOWER_DEP)
			include_directories("${BW_ENGINE_DIR}/${LOWER_DEP}/include")
		endforeach()
	endif()

	# System agnostic headers and sources
	file(GLOB HEADERS      "${INC_BW}/*.h" "${INC_PROJ}/*.h" "${INC_PROJ}/*.inl")
	file(GLOB SOURCES      "${SRC_BW}/*.cpp" "${SRC_PROJ}/*.cpp")
	file(GLOB PRIV_HEADERS "${SRC_PROJ}/*.h" "${SRC_PROJ}/*.inl")

	# System specific headers and source files
	file(GLOB SYS_HEADERS "${INC_PROJ}/${BW_SYSTEM_DIR}/*.inl" "${INC_PROJ}/${BW_SYSTEM_DIR}/*.h")
	file(GLOB SYS_SOURCES "${SRC_PROJ}/${BW_SYSTEM_DIR}/*.cpp" "${SRC_PROJ}/${BW_SYSTEM_DIR}/*.mm")

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

	if (BW_SHARED_LIBS)
		
		add_definitions(-DBW_${PROJECT_UPPER_NAME}_EXPORT)

		# Generate the static library from the sources
		add_library(bw-${PROJECT_LOWER_NAME} SHARED
			${HEADERS}
			${SOURCES}
			${PRIV_HEADERS}
			${SYS_HEADERS}
			${SYS_SOURCES}
			${SYS_SHARED_HEADERS}
			${SYS_SHARED_SOURCES})

		set_target_properties(bw-${PROJECT_LOWER_NAME}
			PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${BW_BASE_DIR}/bin)

	else()

		add_definitions(-DBW_STATIC_LIB)
		
		# Generate the shared library from the sources
		add_library(bw-${PROJECT_LOWER_NAME} STATIC
			${HEADERS}
			${SOURCES}
			${PRIV_HEADERS}
			${SYS_HEADERS}
			${SYS_SOURCES}
			${SYS_SHARED_HEADERS}
			${SYS_SHARED_SOURCES})

	endif()

	if (NOT BW_SYSTEM_WINDOWS)
		add_definitions("-std=c++11")
	endif()

endmacro()

# ===============================================================================
#   Macro to build sample projects
# ===============================================================================
macro(bw_sample SAMPLE_NAME)

	cmake_parse_arguments(THIS "" "GUI_APP" "DEPENDS" ${ARGN})

	string(TOUPPER ${SAMPLE_NAME} UPPER_SAMPLE)
	string(TOLOWER ${SAMPLE_NAME} LOWER_SAMPLE)

	set(SAMPLE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/${LOWER_SAMPLE})

	include_directories("${SAMPLE_DIR}")

	# Headers and sources
	file(GLOB_RECURSE HEADERS "${SAMPLE_DIR}/*.h" "${SAMPLE_DIR}/*.inl")
	file(GLOB_RECURSE SOURCES "${SAMPLE_DIR}/*.cpp" "${SAMPLE_DIR}/*.mm")

	# Source groups (for IDEs)
	source_group("include"  FILES ${HEADERS})
	source_group("src"      FILES ${SOURCES})

	if (THIS_GUI_APP)
		add_executable(${SAMPLE_NAME} WIN32 ${HEADERS} ${SOURCES})
	else()
		add_executable(${SAMPLE_NAME} ${HEADERS} ${SOURCES})
	endif()

	# Include dependency projects
	if (THIS_DEPENDS)
		foreach(DEP ${THIS_DEPENDS})
			string(TOUPPER ${DEP} UPPER_DEP)
			string(TOLOWER ${DEP} LOWER_DEP)

			add_definitions(-DBW_${UPPER_DEP})
			include_directories("${BW_ENGINE_DIR}/${LOWER_DEP}/include")
			target_link_libraries(${SAMPLE_NAME} bw-${LOWER_DEP})
		endforeach()
	endif()


	if (NOT BW_SHARED_LIBS)
		add_definitions(-DBW_STATIC_LIB)
	endif()

	if (NOT BW_SYSTEM_WINDOWS)
		add_definitions("-std=c++11")
	endif()

	if (BW_SYSTEM_EMSCRIPTEN)
		set(CMAKE_EXECUTABLE_SUFFIX ".html")
	endif()

	set_target_properties(${SAMPLE_NAME}
			PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${BW_BASE_DIR}/bin)

endmacro()
