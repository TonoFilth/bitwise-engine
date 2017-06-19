set(LOG_PUBLIC       ${PUBLIC_DIR}/log)
set(LOG_PRIVATE      ${PRIVATE_DIR}/log)
set(PLATFORM_PUBLIC  ${LOG_PUBLIC}/platform/${BW_PLATFORM_DIR})
set(PLATFORM_PRIVATE ${LOG_PRIVATE}/platform/${BW_PLATFORM_DIR})

# Public
list(APPEND SOURCE_FILES
	${PUBLIC_DIR}/log.h
	${LOG_PUBLIC}/log.h
	${LOG_PUBLIC}/log.inl
	${LOG_PUBLIC}/channel.h
	${LOG_PUBLIC}/output.h
	${LOG_PUBLIC}/priority.h
)

# Private
list(APPEND SOURCE_FILES
	${PRIVATE_DIR}/log.cpp
	${LOG_PRIVATE}/log.cpp
	${LOG_PRIVATE}/internal.h
)

set(SOURCE_FILES ${SOURCE_FILES} PARENT_SCOPE)