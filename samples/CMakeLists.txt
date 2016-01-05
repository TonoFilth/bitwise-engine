# Use our custom macro to build all the engine libs
bw_sample("Hello-World"
	GUI_APP FALSE
	DEPENDS "Base")

if (BW_SYSTEM_IOS)
	bw_sample("Hello-iOS"
		GUI_APP FALSE
		DEPENDS "Base" "Memory")
endif()