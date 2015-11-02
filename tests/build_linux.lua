function add_os_options()
    -- ------------------------------
    --  Linux specific configuration
    -- ------------------------------
    buildoptions
    {
        "-std=c++11"
    }
    linkoptions
    {
        "-rdynamic"
    }

    -- ------------------------------
    --  Filters
    -- ------------------------------
    filter "Debug"
        buildoptions
        {
            "-Wall",
            "-Wno-pmf-conversions",
            "-Wno-deprecated-declarations"
        }
        linkoptions
        {
            "-L" .. ENGINE_LIB .. "/static/debug/"
        }

    filter "Release"
        buildoptions
        {
            "-Wall"
        }
        linkoptions
        {
            "-L" .. ENGINE_LIB .. "/static/release/"
        }
end