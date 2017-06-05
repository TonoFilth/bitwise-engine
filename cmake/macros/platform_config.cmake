# ===============================================================================
#   Platform configuration
# ===============================================================================
macro(configure_platform TARGET)

	if (${BW_PLATFORM_WINDOWS})

		

	# -------------------------------------------------------------------------------
	elseif (${BW_PLATFORM_LINUX})

		set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -O0 -ggdb")

		if (${CMAKE_BUILD_TYPE} MATCHES "Debug")
			target_link_libraries(${TARGET} "backtrace")
		endif()

	# -------------------------------------------------------------------------------
	elseif (${BW_PLATFORM_ANDROID})

		message(FATAL_ERROR "Android not configured")

	# -------------------------------------------------------------------------------
	elseif (${BW_PLATFORM_FREEBSD})

		add_definitions("-std=c++11")
		message(FATAL_ERROR "FreeBSD not configured")

	# -------------------------------------------------------------------------------
	elseif (${BW_PLATFORM_IOS})

		message(FATAL_ERROR "iOS not configured")

	# -------------------------------------------------------------------------------
	elseif (${BW_PLATFORM_MACOSX})

		message(FATAL_ERROR "MacOSX not configured")

	# -------------------------------------------------------------------------------
	elseif(${BW_PLATFORM_EMSCRIPTEN})

		message(FATAL_ERROR "Emscripten not configured")
	
	endif()

	# Shared unix configuration
	if (${BW_PLATFORM_UNIX})
		add_definitions("-std=c++11")
	endif()

endmacro()