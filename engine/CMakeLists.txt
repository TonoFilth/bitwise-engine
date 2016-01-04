# Use our custom macro to build all the engine libs
bw_project("Base")
bw_project("Memory" DEPENDS "Base")