set(CORE_PUBLIC      ${PUBLIC_DIR}/core)
set(CORE_PRIVATE     ${PRIVATE_DIR}/core)
set(PLATFORM_PUBLIC  ${CORE_PUBLIC}/platform/${BW_PLATFORM_DIR})
set(PLATFORM_PRIVATE ${CORE_PRIVATE}/platform/${BW_PLATFORM_DIR})

# Public
list(APPEND SOURCE_FILES
	${PUBLIC_DIR}/core.h
	${CORE_PUBLIC}/assert.h
	${CORE_PUBLIC}/bit.h
	${CORE_PUBLIC}/bit.inl
	${CORE_PUBLIC}/callstack.h
	${CORE_PUBLIC}/console.h
	${CORE_PUBLIC}/cstring.h
	${CORE_PUBLIC}/integer.h
	${CORE_PUBLIC}/integer.inl
	${CORE_PUBLIC}/macros.h
	${CORE_PUBLIC}/pointer.h
	${CORE_PUBLIC}/real.h
	${CORE_PUBLIC}/real.inl
	${CORE_PUBLIC}/system.h
)

# Private
list(APPEND SOURCE_FILES
	${PRIVATE_DIR}/core.cpp
	${CORE_PRIVATE}/assert.cpp
	${CORE_PRIVATE}/callstack.cpp
	${CORE_PRIVATE}/cstring.cpp
	${CORE_PRIVATE}/integer.cpp
	${CORE_PRIVATE}/internal.h
	${CORE_PRIVATE}/pointer.cpp
	${CORE_PRIVATE}/real.cpp
)

# Platform sources
if (BW_PLATFORM_WINDOWS)

	list(APPEND SOURCE_FILES
		${PLATFORM_PRIVATE}/windows_assert_handler.cpp
		${PLATFORM_PRIVATE}/windows_callstack.cpp
		${PLATFORM_PRIVATE}/windows_console.cpp
		${PLATFORM_PRIVATE}/windows_cstring.cpp
		${PLATFORM_PRIVATE}/windows_system.cpp
	)

endif()

set(SOURCE_FILES ${SOURCE_FILES} PARENT_SCOPE)