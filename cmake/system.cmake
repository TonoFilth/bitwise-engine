# ===============================================================================
#   Operating system detection
# ===============================================================================
if (${CMAKE_SYSTEM_NAME} MATCHES "Windows")

    set(BW_SYSTEM_WINDOWS 1)
    set(BW_SYSTEM_DIR "windows")

# -------------------------------------------------------------------------------
elseif(${CMAKE_SYSTEM_NAME} MATCHES "Linux")

    set(BW_SYSTEM_UNIX 1)

    if(ANDROID)

        set(BW_SYSTEM_ANDROID 1)
        set(BW_SYSTEM_DIR "android")

    else()

        set(BW_SYSTEM_LINUX 1)
        set(BW_SYSTEM_DIR "linux")

    endif()

# -------------------------------------------------------------------------------
elseif(${CMAKE_SYSTEM_NAME} MATCHES "FreeBSD")
    
    set(BW_SYSTEM_FREEBSD 1)
    set(BW_SYSTEM_DIR "bsd")

# -------------------------------------------------------------------------------
elseif(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")

    set(BW_SYSTEM_UNIX 1)

    if(IOS)
        set(BW_SYSTEM_IOS 1)
        set(BW_SYSTEM_DIR "ios")

    else()

        set(BW_SYSTEM_MACOSX 1)
        set(BW_SYSTEM_DIR "mac")

    endif()

# -------------------------------------------------------------------------------
elseif(${CMAKE_SYSTEM_NAME} MATCHES "Android")

    set(BW_SYSTEM_UNIX    1)
    set(BW_SYSTEM_ANDROID 1)
    set(BW_SYSTEM_DIR "android")

# -------------------------------------------------------------------------------
elseif(${CMAKE_SYSTEM_NAME} MATCHES "Emscripten")

    set(BW_SYSTEM_UNIX       1)
    set(BW_SYSTEM_EMSCRIPTEN 1)
    set(BW_SYSTEM_DIR "web")

# -------------------------------------------------------------------------------
else()
    message(FATAL_ERROR "Unsupported operating system")
    return()
endif()