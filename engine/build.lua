require "android"

--=====================================--
--        SOLUTION DIRECTORIES
--=====================================--
BASE_DIR  = path.getabsolute(path.getdirectory("../")) .. "/"
EXT_INC   = BASE_DIR   .. "extlib/include"
PROJ_DIR  = BASE_DIR   .. "engine/"
BUILD_DIR = PROJ_DIR   .. "build"
LIB_DIR   = PROJ_DIR   .. "lib"
INC_DIR   = PROJ_DIR   .. "include"
SRC_DIR   = PROJ_DIR   .. "src"
-----------------------------------------
function build_project(projectName)
    local lowerName = string.lower(projectName)
    local upperName = string.upper(projectName)

    local includeDir = INC_DIR .. "/Bw/" .. projectName
    local srcDir     = SRC_DIR .. "/Bw/" .. projectName

    project(projectName)
        language "C++"
        files
        {
            includeDir .. "/**.h",
            includeDir .. "/**.inl",
            srcDir     .. "/**.h",
            srcDir     .. "/**.cpp",
            INC_DIR    .. "/Bw/" .. projectName .. ".h",
            SRC_DIR    .. "/Bw/" .. projectName .. ".cpp"
        }
        includedirs
        {
            EXT_INC,
            INC_DIR,
            SRC_DIR
        }

        targetname("bw-" .. lowerName)

        -- OS options
        if _ACTION == "android" then
            include(PROJ_DIR .. "build_android.lua")
        else
            include(PROJ_DIR .. "build_" .. os.get() .. ".lua")
        end
        add_os_options()

        -- Special files
        if projectName == "Base" then
            files
            {
                INC_DIR .. "/Bw/Bw.h",
                SRC_DIR .. "/Bw/Bw.cpp"
            }
        end

        -- Static libraries
        filter "Debug or Release"
            kind "StaticLib"
            defines { "BW_STATIC_LIB" }

        -- Shared libraries
        filter "Debug_SO or Release_SO"
            kind "SharedLib"
            defines { "BW_" .. upperName .. "_EXPORT" }

        -- Static debug library config
        filter "Debug"
            targetsuffix "-sd"
            targetdir(LIB_DIR .. "/static/debug")

        -- Static release library config
        filter "Release"
            targetsuffix "-s"
            targetdir(LIB_DIR .. "/static/release")
            
        -- Shared debug library config
        filter "Debug_SO"
            targetsuffix "-d"
            targetdir(LIB_DIR .. "/shared/debug")

        -- Shared release library config
        filter "Release_SO"
            targetdir(LIB_DIR .. "/shared/release")
end

--=====================================--
--               SOLUTION
--=====================================--
workspace "Bitwise Engine"

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

    -- Include child projects
    build_project("Base")
    --build_project("Foundation")