include(CMakeParseArguments)

# ===============================================================================
#   Macro to build test projects
# ===============================================================================
macro(bw_test MODULE_NAME)

	cmake_parse_arguments(THIS "" "GUI_APP" "DEPENDS" ${ARGN})

	string(TOLOWER ${MODULE_NAME} LOWER_MODULE)
	string(TOUPPER ${MODULE_NAME} UPPER_MODULE)

	set(TEST_DIR ${CMAKE_CURRENT_SOURCE_DIR})
	set(TARGET   bw-${LOWER_MODULE}-tests)

	include_directories(${TEST_DIR})
	include_directories(${BW_EXTLIB_DIR}/include)

	# Headers and sources
	file(GLOB_RECURSE HEADERS "${TEST_DIR}/*.h"   "${TEST_DIR}/*.inl")
	file(GLOB_RECURSE SOURCES "${TEST_DIR}/*.cpp" "${TEST_DIR}/*.mm")

	# Source groups (for IDEs)
	source_group("include"  FILES ${HEADERS})
	source_group("src"      FILES ${SOURCES})

	if (THIS_GUI_APP)
		add_executable(${TARGET} WIN32 ${HEADERS} ${SOURCES})
	else()
		add_executable(${TARGET} ${HEADERS} ${SOURCES})
	endif()

	# Include dependency projects
	if (THIS_DEPENDS)
		foreach(DEP ${THIS_DEPENDS})
			string(TOUPPER ${DEP} UPPER_DEP)
			string(TOLOWER ${DEP} LOWER_DEP)

			add_definitions(-DBW_${UPPER_DEP})
			include_directories("${BW_ENGINE_DIR}/${LOWER_DEP}/include")
			target_link_libraries(${TARGET} bw-${LOWER_DEP})

			if (${LOWER_DEP} MATCHES ${LOWER_MODULE})
				set(BW_TESTED_MODULE_DEP_SET TRUE)
			endif()

			if (THIS_GUI_APP AND ${LOWER_DEP} MATCHES "main")
				set(BW_MAIN_LINKED TRUE)
			endif()
		endforeach()
	endif()

	# If this is a Windowed app make sure we statically
	# link with bw-main to have a cross-platform entry point
	if (NOT BW_MAIN_LINKED AND THIS_GUI_APP)
		target_link_libraries(${TARGET} bw-main)
	endif()

	if (NOT BW_TESTED_MODULE_DEP_SET)
		message(FATAL_ERROR "Tested module not set as a dependency")
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

	set_target_properties(${TARGET}
		PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${BW_BASE_DIR}/bin)

endmacro()