# Module config
set(MODULE_NAME      core)
set(MODULE_PUBLIC    ${PUBLIC_DIR}/${MODULE_NAME})
set(MODULE_PRIVATE   ${PRIVATE_DIR}/${MODULE_NAME})
set(PLATFORM_PUBLIC  ${MODULE_PUBLIC}/platform/${BW_PLATFORM_DIR})
set(PLATFORM_PRIVATE ${MODULE_PRIVATE}/platform/${BW_PLATFORM_DIR})

# Public
list(APPEND SOURCE_FILES
	${PUBLIC_DIR}/${MODULE_NAME}.h
	${MODULE_PUBLIC}/assert.h
	${MODULE_PUBLIC}/bit.h
	${MODULE_PUBLIC}/bit.inl
	${MODULE_PUBLIC}/callstack.h
	${MODULE_PUBLIC}/console.h
	${MODULE_PUBLIC}/cstring.h
	${MODULE_PUBLIC}/integer.h
	${MODULE_PUBLIC}/integer.inl
	${MODULE_PUBLIC}/macros.h
	${MODULE_PUBLIC}/pointer.h
	${MODULE_PUBLIC}/real.h
	${MODULE_PUBLIC}/real.inl
	${MODULE_PUBLIC}/system.h
)

# Private
list(APPEND SOURCE_FILES
	${PRIVATE_DIR}/${MODULE_NAME}.cpp
	${MODULE_PRIVATE}/assert.cpp
	${MODULE_PRIVATE}/callstack.cpp
	${MODULE_PRIVATE}/cstring.cpp
	${MODULE_PRIVATE}/integer.cpp
	${MODULE_PRIVATE}/internal.h
	${MODULE_PRIVATE}/pointer.cpp
	${MODULE_PRIVATE}/real.cpp
)

# Platform sources
if (BW_PLATFORM_WINDOWS)

	list(APPEND SOURCE_FILES
		${PLATFORM_PRIVATE}/windows_assert.cpp
		${PLATFORM_PRIVATE}/windows_callstack.cpp
		${PLATFORM_PRIVATE}/windows_console.cpp
		${PLATFORM_PRIVATE}/windows_cstring.cpp
		${PLATFORM_PRIVATE}/windows_system.cpp
	)

endif()

set(SOURCE_FILES ${SOURCE_FILES} PARENT_SCOPE)