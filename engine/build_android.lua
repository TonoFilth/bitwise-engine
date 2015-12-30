function add_os_options()
    -- ------------------------------
    --  Android specific configuration
    -- ------------------------------
    excludes
    {
        INC_DIR .. "/**/Windows/*",
        SRC_DIR .. "/**/Windows/*"
    }
    buildoptions
    {
        "-std=c++11"
    }

    -- --------------------------------
    --  Filters
    -- --------------------------------
    filter { "Debug or Debug_SO" }
        buildoptions
        {
            "-Wall",
            "-Wno-pmf-conversions",
            "-Wno-deprecated-declarations"
        }

    --filter { "Release or Release_SO" }
end