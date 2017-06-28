# Module config
set(MODULE_NAME      collections)
set(MODULE_PUBLIC    ${PUBLIC_DIR}/${MODULE_NAME})
set(MODULE_PRIVATE   ${PRIVATE_DIR}/${MODULE_NAME})
set(PLATFORM_PUBLIC  ${MODULE_PUBLIC}/platform/${BW_PLATFORM_DIR})
set(PLATFORM_PRIVATE ${MODULE_PRIVATE}/platform/${BW_PLATFORM_DIR})

# Public
list(APPEND SOURCE_FILES
	${PUBLIC_DIR}/${MODULE_NAME}.h
	${MODULE_PUBLIC}/array.h
	${MODULE_PUBLIC}/array/array.inl
	${MODULE_PUBLIC}/list.h
	${MODULE_PUBLIC}/list/list.inl
	${MODULE_PUBLIC}/list/list_iterator.h
	${MODULE_PUBLIC}/list/list_iterator.inl
	${MODULE_PUBLIC}/list/list_node.h
)

# Private
list(APPEND SOURCE_FILES
	${PRIVATE_DIR}/${MODULE_NAME}.cpp
	${MODULE_PRIVATE}/internal.h
)

set(SOURCE_FILES ${SOURCE_FILES} PARENT_SCOPE)