# Include all samples
add_subdirectory(${BW_SAMPLE_DIR}/hello-world)

# Temporal
if (BW_SYSTEM_IOS)
	add_subdirectory(${BW_SAMPLE_DIR}/hello-iOS)
endif()