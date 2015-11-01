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
            srcDir     .. "/**.cpp"
        }
        includedirs
        {
            EXT_INC,
            INC_DIR
        }

        targetname("bw-" .. lowerName)

        -- Static libraries
        filter "Debug or Release"
            kind "StaticLib"
            defines { "BW_STATIC_LIB" }

        -- Shared libraries
        filter "Debug_DLL or Release_DLL"
            kind "SharedLib"



        -- Static debug library config
        filter "Debug"
            targetsuffix "-sd"
            targetdir(LIB_DIR .. "/static/debug")

        -- Static release library config
        filter "Release"
            targetsuffix "-s"
            targetdir(LIB_DIR .. "/static/release")
            
        -- Shared debug library config
        filter "Debug_DLL"
            targetsuffix "-d"
            targetdir(LIB_DIR .. "/shared/debug")
            defines { "BW_" .. upperName .. "_EXPORT" }

        -- Shared release library config
        filter "Release_DLL"
            targetdir(LIB_DIR .. "/shared/release")
            defines { "BW_" .. upperName .. "_EXPORT" }
end

--=====================================--
--               SOLUTION
--=====================================--
workspace "Bitwise Engine"

    -- Standard project configurations
    configurations { "Debug", "Release", "Debug_DLL", "Release_DLL" }

    -- Project platforms
    platforms { "x64" }

    -- Directory where the Makefile/Solution will be generated
    location(BUILD_DIR)

    -- Common debug options
   filter "Debug or Debug_DLL"
        flags { "Symbols" }
        optimize "Off"

    -- Common release options
    filter "Release or Release_DLL"
        defines { "NDEBUG" }
        optimize "Speed"

    -- Include child projects
    build_project("Base")
    build_project("Foundation")