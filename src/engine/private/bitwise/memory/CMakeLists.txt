set(MEMORY_PUBLIC    ${PUBLIC_DIR}/memory)
set(MEMORY_PRIVATE   ${PRIVATE_DIR}/memory)
set(PLATFORM_PUBLIC  ${MEMORY_PUBLIC}/platform/${BW_PLATFORM_DIR})
set(PLATFORM_PRIVATE ${MEMORY_PRIVATE}/platform/${BW_PLATFORM_DIR})

# Public
list(APPEND SOURCE_FILES
	${PUBLIC_DIR}/memory.h
	${MEMORY_PUBLIC}/allocator.h
	${MEMORY_PUBLIC}/allocator.inl
	${MEMORY_PUBLIC}/fwd.h
	${MEMORY_PUBLIC}/global_allocators.h
	${MEMORY_PUBLIC}/heap_allocator.h
	${MEMORY_PUBLIC}/page_allocator.h
	${MEMORY_PUBLIC}/scope_allocator.h
	${MEMORY_PUBLIC}/scope_allocator.inl
	${MEMORY_PUBLIC}/trace_allocator.h
)

# Private
list(APPEND SOURCE_FILES
	${PRIVATE_DIR}/memory.cpp
	${MEMORY_PRIVATE}/internal.h
	${MEMORY_PRIVATE}/global_allocators.cpp
	${MEMORY_PRIVATE}/heap_allocator.cpp
	${MEMORY_PRIVATE}/page_allocator.cpp
	${MEMORY_PRIVATE}/trace_allocator.cpp
)

# Platform sources
if (BW_PLATFORM_WINDOWS)

	list(APPEND SOURCE_FILES
		${PLATFORM_PRIVATE}/windows_alloc.cpp
		${PLATFORM_PRIVATE}/windows_page_allocator.cpp
	)

endif()

set(SOURCE_FILES ${SOURCE_FILES} PARENT_SCOPE)