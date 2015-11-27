--=====================================--
--        SOLUTION DIRECTORIES
--=====================================--
BASE_DIR   = path.getabsolute(path.getdirectory("../")) .. "/"
EXT_INC    = BASE_DIR   .. "extlib/include"
EXT_LIB    = BASE_DIR   .. "extlib/lib"
ENGINE_DIR = BASE_DIR   .. "engine/"
ENGINE_INC = ENGINE_DIR .. "include"
ENGINE_LIB = ENGINE_DIR .. "lib"
PROJ_DIR   = BASE_DIR   .. "samples/"
BIN_DIR    = PROJ_DIR   .. "bin"
BUILD_DIR  = PROJ_DIR   .. "build"
INC_DIR    = PROJ_DIR   .. "include"
SRC_DIR    = PROJ_DIR   .. "src"
-----------------------------------------
function create_libTable(libs)
    local libTable =
    {
        ["Debug"]      = {},
        ["Debug_SO"]   = {},
        ["Release"]    = {},
        ["Release_SO"] = {},
        ["defines"]    = {}
    }

    for idx,lib in ipairs(libs) do
        local lowerName = string.lower(lib)
        local upperName = string.upper(lib)

        table.insert(libTable["Debug"],      "bw-" .. lowerName .. "-sd")
        table.insert(libTable["Release"],    "bw-" .. lowerName .. "-s")
        table.insert(libTable["Debug_SO"],   "bw-" .. lowerName .. "-d")
        table.insert(libTable["Release_SO"], "bw-" .. lowerName)
        table.insert(libTable["defines"],    "BW_" .. upperName)
    end

    return libTable
end
-----------------------------------------
function build_sample(sampleName, lib, linkLibs)
    local lowerName = string.lower(sampleName)
    local upperName = string.upper(sampleName)

    local includeDir = INC_DIR .. "/Bw/Samples/" .. lib .. "/" .. sampleName
    local srcDir     = SRC_DIR .. "/Bw/Samples/" .. lib .. "/" .. sampleName

    local libTable = create_libTable(linkLibs)

    project(sampleName)
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
            "BW_SAMPLE"
        }
        defines(libTable["defines"])
        targetname(sampleName)

        -- OS options
        include(PROJ_DIR .. "build_" .. os.get() .. ".lua")
        add_os_options()

        -- Links sample app with engine static debug libraries
        filter "Debug"
            targetdir(BIN_DIR .. "/static/debug/")
            links(libTable["Debug"])
            libdirs
            {
                EXT_LIB    .. "/debug/",
                ENGINE_LIB .. "/static/debug/"
            }
            defines
            {
                "BW_STATIC_LIB"
            }

        -- Links sample app with engine static release libraries
        filter "Release"
            targetdir(BIN_DIR .. "/static/release/")
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

         -- Links sample app with engine static debug libraries
        filter "Debug_SO"
            targetdir(BIN_DIR .. "/shared/debug/")
            links(libTable["Debug_SO"])
            libdirs
            {
                EXT_LIB    .. "/debug",
                ENGINE_LIB .. "/shared/debug"
            }

        -- Links sample app with engine static release libraries
        filter "Release_SO"
            targetdir(BIN_DIR .. "/shared/release/")
            links(libTable["Release_SO"])
            libdirs
            {
                EXT_LIB    .. "/release",
                ENGINE_LIB .. "/shared/release"
            }
end

--=====================================--
--               SOLUTION
--=====================================--
workspace "Bitwise Engine (Samples)"

    -- Standard project configurations
    configurations { "Debug", "Release", "Debug_SO", "Release_SO" }

    -- Project platforms
    platforms { "x64" }

    -- Directory where the Makefile/Solution will be generated
    location(BUILD_DIR)

    -- Common debug options
   filter "Debug or Debug_SO"
        flags { "Symbols" }
        optimize "Off"

    -- Common release options
    filter "Release or Release_SO"
        defines { "NDEBUG" }
        optimize "Speed"

    -- Build all samples
    build_sample("HelloWorld", "Base", {"Base"})
    --build_sample("Foundation", "Foundation", {"Base", "Foundation"})