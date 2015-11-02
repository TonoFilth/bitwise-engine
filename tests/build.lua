--=====================================--
--        SOLUTION DIRECTORIES
--=====================================--
BASE_DIR   = path.getabsolute(path.getdirectory("../")) .. "/"
EXT_INC    = BASE_DIR   .. "extlib/include"
EXT_LIB    = BASE_DIR   .. "extlib/lib"
ENGINE_DIR = BASE_DIR   .. "engine/"
ENGINE_INC = ENGINE_DIR .. "include"
ENGINE_LIB = ENGINE_DIR .. "lib"
PROJ_DIR   = BASE_DIR   .. "tests/"
BIN_DIR    = PROJ_DIR   .. "bin"
BUILD_DIR  = PROJ_DIR   .. "build"
INC_DIR    = PROJ_DIR   .. "include"
SRC_DIR    = PROJ_DIR   .. "src"
-----------------------------------------
function create_lib_table(libs)
    local lib_table =
    {
        ["Debug"]   = {},
        ["Release"] = {},
        ["defines"] = {}
    }

    for idx,lib in ipairs(libs) do
        local lowerName = string.lower(lib)
        local upperName = string.upper(lib)

        table.insert(lib_table["Debug"],   "bw-" .. lowerName .. "-sd")
        table.insert(lib_table["Release"], "bw-" .. lowerName .. "-s")
        table.insert(lib_table["defines"], "BW_" .. upperName)
    end

    return lib_table
end
-----------------------------------------
function build_tests(lib, link_libs)
    local lowerName = string.lower(lib)
    local upperName = string.upper(lib)

    local includeDir = INC_DIR .. "/" .. lib
    local srcDir     = SRC_DIR .. "/" .. lib

    local lib_table = create_lib_table(link_libs)

    project(lowerName .. "-tests")
        kind    "ConsoleApp"
        language "C++"
        files
        {
            includeDir .. "/**.h",
            includeDir .. "/**.inl",
            srcDir     .. "/**.cpp"
        }
        includedirs
        {
            EXT_INC,
            INC_DIR,
            ENGINE_INC
        }
        defines
        {
            "BW_TEST"
        }
        defines(lib_table["defines"])
        targetname(lowerName .. "-tests")

        -- OS options
        include(PROJ_DIR .. "build_" .. os.get() .. ".lua")
        add_os_options()

        -- Links sample app with engine static debug libraries
        filter "Debug"
            targetdir(BIN_DIR .. "/debug")
            links(lib_table["Debug"])
            libdirs
            {
                EXT_LIB    .. "/debug",
                ENGINE_LIB .. "/static/debug"
            }
            defines
            {
                "BW_STATIC_LIB"
            }
            linkoptions
            {
                "-L" .. ENGINE_LIB .. "/static/debug/"
            }

        -- Links sample app with engine static release libraries
        filter "Release"
            targetdir(BIN_DIR .. "/release")
            links(lib_table["Release"])
            libdirs
            {
                EXT_LIB    .. "/release",
                ENGINE_LIB .. "/static/release"
            }
            defines
            {
                "BW_STATIC_LIB"
            }
            linkoptions
            {
                "-L" .. ENGINE_LIB .. "/static/release/"
            }
end

--=====================================--
--               SOLUTION
--=====================================--
workspace "Bitwise Engine (Tests)"

    -- Standard project configurations
    configurations { "Debug", "Release" }

    -- Project platforms
    platforms { "x64" }

    -- Directory where the Makefile/Solution will be generated
    location(BUILD_DIR)

    -- Common debug options
   filter "Debug"
        flags { "Symbols" }
        optimize "Off"

    -- Common release options
    filter "Release"
        defines { "NDEBUG" }
        optimize "Speed"

    -- Build all samples
    build_tests("Base",       {"Base"})
    build_tests("Foundation", {"Base", "Foundation"})