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
    filter { "Debug or Debug_SO" }
        buildoptions
        {
            "-Wall",
            "-Wno-pmf-conversions",
            "-Wno-deprecated-declarations"
        }

    filter { "Release or Release_SO" }
        buildoptions
        {
            "-Wall"
        }

    filter "Debug"
        linkoptions
        {
            "-L" .. ENGINE_LIB .. "/static/debug/"
        }

    filter "Release"
        linkoptions
        {
            "-L" .. ENGINE_LIB .. "/static/release/"
        }

    filter "Debug_SO"
        linkoptions
        {
            "-L" .. ENGINE_LIB .. "/shared/debug/"
        }

    filter "Release_SO"
        linkoptions
        {
            "-L" .. ENGINE_LIB .. "/shared/release/"
        }
end