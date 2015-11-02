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
function create_lib_table(libs)
    local lib_table =
    {
        ["Debug"]       = {},
        ["Debug_SHD"]   = {},
        ["Release"]     = {},
        ["Release_SHD"] = {},
        ["defines"]     = {}
    }

    for idx,lib in ipairs(libs) do
        local lowerName = string.lower(lib)
        local upperName = string.upper(lib)

        table.insert(lib_table["Debug"],       "bw-" .. lowerName .. "-sd")
        table.insert(lib_table["Release"],     "bw-" .. lowerName .. "-s")
        table.insert(lib_table["Debug_SHD"],   "bw-" .. lowerName .. "-d")
        table.insert(lib_table["Release_SHD"], "bw-" .. lowerName)
        table.insert(lib_table["defines"],     "BW_" .. upperName)
    end

    return lib_table
end
-----------------------------------------
function build_sample(sampleName, libs)
    local lowerName = string.lower(sampleName)
    local upperName = string.upper(sampleName)

    local includeDir = INC_DIR .. "/" .. sampleName
    local srcDir     = SRC_DIR .. "/" .. sampleName

    local lib_table = create_lib_table(libs)

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
        defines(lib_table["defines"])
        targetname(sampleName)

        -- OS options
        include(PROJ_DIR .. "build_" .. os.get() .. ".lua")
        add_os_options()

        -- Links sample app with engine static debug libraries
        filter "Debug"
            targetdir(BIN_DIR .. "/static/debug")
            links(lib_table["Debug"])
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
            targetdir(BIN_DIR .. "/static/release")
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

         -- Links sample app with engine static debug libraries
        filter "Debug_SHD"
            targetdir(BIN_DIR .. "/shared/debug")
            links(lib_table["Debug_SHD"])
            libdirs
            {
                EXT_LIB    .. "/debug",
                ENGINE_LIB .. "/shared/debug"
            }

        -- Links sample app with engine static release libraries
        filter "Release_SHD"
            targetdir(BIN_DIR .. "/shared/release")
            links(lib_table["Release_SHD"])
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
    configurations { "Debug", "Release", "Debug_SHD", "Release_SHD" }

    -- Project platforms
    platforms { "x64" }

    -- Directory where the Makefile/Solution will be generated
    location(BUILD_DIR)

    -- Common debug options
   filter "Debug or Debug_SHD"
        flags { "Symbols" }
        optimize "Off"

    -- Common release options
    filter "Release or Release_SHD"
        defines { "NDEBUG" }
        optimize "Speed"

    -- Build all samples
    build_sample("HelloWorld", {"Base"})
    build_sample("Foundation", {"Base", "Foundation"})