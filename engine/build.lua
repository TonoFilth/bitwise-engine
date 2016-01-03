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

    project(projectName)
        language "C++"
        files
        {
            INC_DIR .. "/Bw/" .. projectName .. "/**.h",
            INC_DIR .. "/Bw/" .. projectName .. "/**.inl",
            SRC_DIR .. "/Bw/" .. projectName .. "/**.h",
            SRC_DIR .. "/Bw/" .. projectName .. "/**.cpp",
            INC_DIR .. "/Bw/" .. projectName .. ".h",
            SRC_DIR .. "/Bw/" .. projectName .. ".cpp"
        }
        if projectName == "Base" then
            files
            {
                INC_DIR .. "/Bw/Bw.h",
                INC_DIR .. "/Bw/Memory.h",
                INC_DIR .. "/Bw/Memory/**.h",
                INC_DIR .. "/Bw/Concurrency.h",
                INC_DIR .. "/Bw/Concurrency/**.h",
                SRC_DIR .. "/Bw/Memory.cpp",
                SRC_DIR .. "/Bw/Memory/**.h",
                SRC_DIR .. "/Bw/Memory/**.cpp",
                SRC_DIR .. "/Bw/Concurrency.cpp",
                SRC_DIR .. "/Bw/Concurrency/**.h",
                SRC_DIR .. "/Bw/Concurrency/**.cpp"
            }
        end
        includedirs
        {
            EXT_INC,
            INC_DIR,
            SRC_DIR
        }
        objdir(BUILD_DIR .. "/obj")
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
        filter "Static*"
            kind "StaticLib"
            defines { "BW_STATIC_LIB" }

        -- Shared libraries
        filter "Shared*"
            kind "SharedLib"
            defines { "BW_" .. upperName .. "_EXPORT" }

        -- Static debug library config
        filter "Static_Debug"
            targetsuffix "-sd"
            targetdir(LIB_DIR .. "/static/debug")

        -- Static release library config
        filter "Static_Release"
            targetsuffix "-s"
            targetdir(LIB_DIR .. "/static/release")
            
        -- Shared debug library config
        filter "Shared_Debug"
            targetsuffix "-d"
            targetdir(LIB_DIR .. "/shared/debug")

        -- Shared release library config
        filter "Shared_Release"
            targetdir(LIB_DIR .. "/shared/release")
end

--=====================================--
--               SOLUTION
--=====================================--
workspace "Bitwise Engine"
    -- Standard project configurations
    configurations
    {
        "Static_Debug", "Static_Release",
        "Shared_Debug", "Shared_Release"
    }

    -- Project platforms
    --platforms { "x64", "x86" }
    platforms { "x64" }

    -- Directory where the Makefile/Solution will be generated
    location(BUILD_DIR)

    -- Common debug options
   filter "*Debug"
        flags { "Symbols" }
        optimize "Off"

    -- Common release options
    filter "*Release"
        defines { "NDEBUG" }
        optimize "Speed"

    -- Include child projects
    build_project("Base")
    --build_project("Foundation")