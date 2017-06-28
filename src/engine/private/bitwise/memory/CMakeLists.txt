# Module config
set(MODULE_NAME      memory)
set(MODULE_PUBLIC    ${PUBLIC_DIR}/${MODULE_NAME})
set(MODULE_PRIVATE   ${PRIVATE_DIR}/${MODULE_NAME})
set(PLATFORM_PUBLIC  ${MODULE_PUBLIC}/platform/${BW_PLATFORM_DIR})
set(PLATFORM_PRIVATE ${MODULE_PRIVATE}/platform/${BW_PLATFORM_DIR})

# Public
list(APPEND SOURCE_FILES
	${PUBLIC_DIR}/${MODULE_NAME}.h
	${MODULE_PUBLIC}/allocator.h
	${MODULE_PUBLIC}/allocator.inl
	${MODULE_PUBLIC}/fwd.h
	${MODULE_PUBLIC}/global_allocators.h
	${MODULE_PUBLIC}/heap_allocator.h
	${MODULE_PUBLIC}/page_allocator.h
	${MODULE_PUBLIC}/scope_allocator.h
	${MODULE_PUBLIC}/scope_allocator.inl
	${MODULE_PUBLIC}/trace_allocator.h
)

# Private
list(APPEND SOURCE_FILES
	${PRIVATE_DIR}/${MODULE_NAME}.cpp
	${MODULE_PRIVATE}/internal.h
	${MODULE_PRIVATE}/global_allocators.cpp
	${MODULE_PRIVATE}/heap_allocator.cpp
	${MODULE_PRIVATE}/page_allocator.cpp
	${MODULE_PRIVATE}/trace_allocator.cpp
)

# Platform sources
if (BW_PLATFORM_WINDOWS)

	list(APPEND SOURCE_FILES
		${PLATFORM_PRIVATE}/windows_alloc.cpp
		${PLATFORM_PRIVATE}/windows_page_allocator.cpp
	)

endif()

set(SOURCE_FILES ${SOURCE_FILES} PARENT_SCOPE)