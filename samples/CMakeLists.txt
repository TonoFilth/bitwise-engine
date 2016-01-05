# Use our custom macro to build all the engine libs
bw_sample("Hello-World"
	GUI_APP FALSE
	DEPENDS "Base" "Memory")

bw_sample("Hello-iOS"
	GUI_APP FALSE
	DEPENDS "Base" "Memory")