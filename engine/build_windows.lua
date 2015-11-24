function add_os_options(projectName)
    -- --------------------------------
    --  Windows specific configuration
    -- --------------------------------
    includedirs
    {
        SRC_DIR .. "Bw/" .. projectName .. "/__sys/Windows/"
    }
    excludes
    {
        INC_DIR .. "/**/Unix/*",
        SRC_DIR .. "/**/Unix/*"
    }

    -- --------------------------------
    --  Filters
    -- --------------------------------
end