include(CMakeParseArguments)

# ===============================================================================
#   Macro to build sample projects
# ===============================================================================
macro(bw_sample SAMPLE_NAME)

	cmake_parse_arguments(THIS "" "GUI_APP" "DEPENDS" ${ARGN})

	string(TOUPPER ${SAMPLE_NAME} UPPER_SAMPLE)
	string(TOLOWER ${SAMPLE_NAME} LOWER_SAMPLE)

	set(SAMPLE_DIR ${CMAKE_CURRENT_SOURCE_DIR})

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

			if (THIS_GUI_APP AND ${LOWER_DEP} MATCHES "main")
				set(BW_MAIN_LINKED TRUE)
			endif()
		endforeach()
	endif()

	# If this is a Windowed app make sure we statically
	# link with bw-main to have a cross-platform entry point
	if (NOT BW_MAIN_LINKED AND THIS_GUI_APP)
		target_link_libraries(${SAMPLE_NAME} bw-main)
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