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
function create_libTable(libs)
    local libTable =
    {
        ["Debug"]   = {},
        ["Release"] = {},
        ["defines"] = {}
    }

    for idx,lib in ipairs(libs) do
        local lowerName = string.lower(lib)
        local upperName = string.upper(lib)

        table.insert(libTable["Debug"],   "bw-" .. lowerName .. "-sd")
        table.insert(libTable["Release"], "bw-" .. lowerName .. "-s")
        table.insert(libTable["defines"], "BW_" .. upperName)
    end

    return libTable
end
-----------------------------------------
function build_tests(lib, linkLibs)
    local lowerName = string.lower(lib)
    local upperName = string.upper(lib)

    local includeDir = INC_DIR .. "/Bw/Tests/" .. lib
    local srcDir     = SRC_DIR .. "/Bw/Tests/" .. lib

    local libTable = create_libTable(linkLibs)

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
        defines(libTable["defines"])
        targetname(lowerName .. "-tests")

        -- OS options
        include(PROJ_DIR .. "build_" .. os.get() .. ".lua")
        add_os_options()

        -- Links test app with engine static debug libraries
        filter "Debug"
            targetdir(BIN_DIR .. "/debug/" .. lib)
            links(libTable["Debug"])
            libdirs
            {
                EXT_LIB    .. "/debug",
                ENGINE_LIB .. "/static/debug"
            }
            defines
            {
                "BW_STATIC_LIB"
            }

        -- Links test app with engine static release libraries
        filter "Release"
            targetdir(BIN_DIR .. "/release/" .. lib)
            links(libTable["Release"])
            libdirs
            {
                EXT_LIB    .. "/release",
                ENGINE_LIB .. "/static/release"
            }
            defines
            {
                "BW_STATIC_LIB"
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

    -- Build all tests
    build_tests("Base", {"Base"})
    --build_tests("Foundation", {"Base", "Foundation"})