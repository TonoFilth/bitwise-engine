function add_os_options()
    -- --------------------------------
    --  Windows specific configuration
    -- --------------------------------
    excludes
    {
        INC_DIR .. "/**/Unix/*",
        SRC_DIR .. "/**/Unix/*",
        INC_DIR .. "/**/Android/*",
        SRC_DIR .. "/**/Android/*"
    }

    -- --------------------------------
    --  Filters
    -- --------------------------------
end