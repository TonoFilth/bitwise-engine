# ===============================================================================
#   Operating system detection
# ===============================================================================
if (${CMAKE_SYSTEM_NAME} MATCHES "Windows")

    set(BW_SYSTEM_WINDOWS 1)
    set(BW_SYSTEM_DIR "Windows")

# -------------------------------------------------------------------------------
elseif(${CMAKE_SYSTEM_NAME} MATCHES "Linux")

    set(BW_SYSTEM_UNIX 1)

    if(ANDROID)

        set(BW_SYSTEM_ANDROID 1)
        set(BW_SYSTEM_DIR "Android")

    else()

        set(BW_SYSTEM_LINUX 1)
        set(BW_SYSTEM_DIR "Linux")

    endif()

# -------------------------------------------------------------------------------
elseif(${CMAKE_SYSTEM_NAME} MATCHES "FreeBSD")
    
    set(BW_SYSTEM_FREEBSD 1)
    set(BW_SYSTEM_DIR "FreeBSD")

# -------------------------------------------------------------------------------
elseif(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")

    set(BW_SYSTEM_UNIX 1)

    if(IOS)
        set(BW_SYSTEM_IOS 1)
        set(BW_SYSTEM_DIR "iOS")

    else()

        set(BW_SYSTEM_MACOSX 1)
        set(BW_SYSTEM_DIR "MacOSX")

    endif()

# -------------------------------------------------------------------------------
elseif(${CMAKE_SYSTEM_NAME} MATCHES "Android")

    set(BW_SYSTEM_UNIX    1)
    set(BW_SYSTEM_ANDROID 1)
    set(BW_SYSTEM_DIR "Android")

# -------------------------------------------------------------------------------
elseif(${CMAKE_SYSTEM_NAME} MATCHES "Emscripten")

    set(BW_SYSTEM_UNIX       1)
    set(BW_SYSTEM_EMSCRIPTEN 1)
    set(BW_SYSTEM_DIR        "Web")

# -------------------------------------------------------------------------------
else()
    message(FATAL_ERROR "Unsupported operating system")
    return()
endif()