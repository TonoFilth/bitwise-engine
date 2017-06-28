# Module config
set(MODULE_NAME      network)
set(MODULE_PUBLIC    ${PUBLIC_DIR}/${MODULE_NAME})
set(MODULE_PRIVATE   ${PRIVATE_DIR}/${MODULE_NAME})
set(PLATFORM_PUBLIC  ${MODULE_PUBLIC}/platform/${BW_PLATFORM_DIR})
set(PLATFORM_PRIVATE ${MODULE_PRIVATE}/platform/${BW_PLATFORM_DIR})

# Public
list(APPEND SOURCE_FILES
	${PUBLIC_DIR}/${MODULE_NAME}.h
	${MODULE_PUBLIC}/module_internal.h
	${MODULE_PUBLIC}/tcp/tcp_client.h
	${MODULE_PUBLIC}/tcp/tcp_client_config.h
	${MODULE_PUBLIC}/tcp/tcp_server.h
	${MODULE_PUBLIC}/tcp/tcp_server_config.h
)

# Private
list(APPEND SOURCE_FILES
	${PRIVATE_DIR}/${MODULE_NAME}.cpp
	${MODULE_PRIVATE}/internal.h
)

# Platform sources
if (BW_PLATFORM_WINDOWS)

	list(APPEND SOURCE_FILES
		${PLATFORM_PRIVATE}/tcp/windows_tcp_types.h
		${PLATFORM_PRIVATE}/tcp/windows_tcp_client.cpp
		${PLATFORM_PRIVATE}/tcp/windows_tcp_server.cpp
	)

endif()

set(SOURCE_FILES ${SOURCE_FILES} PARENT_SCOPE)