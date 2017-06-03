# ===============================================================================
#   Platform detection
# ===============================================================================
if (${CMAKE_SYSTEM_NAME} MATCHES "Windows")

    set(BW_PLATFORM_WINDOWS 1)
    set(BW_PLATFORM_DIR "windows")

# -------------------------------------------------------------------------------
elseif(${CMAKE_SYSTEM_NAME} MATCHES "Linux")

    set(BW_PLATFORM_UNIX 1)
    
    if(ANDROID)

        set(BW_PLATFORM_ANDROID 1)
        set(BW_PLATFORM_DIR "android")

    else()

        set(BW_PLATFORM_LINUX 1)
        set(BW_PLATFORM_DIR "linux")

    endif()

# -------------------------------------------------------------------------------
elseif(${CMAKE_SYSTEM_NAME} MATCHES "FreeBSD")
    
    set(BW_PLATFORM_FREEBSD 1)
    set(BW_PLATFORM_DIR "bsd")

# -------------------------------------------------------------------------------
elseif(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")

    set(BW_PLATFORM_UNIX 1)

    if(IOS)
        set(BW_PLATFORM_IOS 1)
        set(BW_PLATFORM_DIR "ios")

    else()

        set(BW_PLATFORM_MACOSX 1)
        set(BW_PLATFORM_DIR "mac")

    endif()

# -------------------------------------------------------------------------------
elseif(${CMAKE_SYSTEM_NAME} MATCHES "Android")

    set(BW_PLATFORM_UNIX    1)
    set(BW_PLATFORM_ANDROID 1)
    set(BW_PLATFORM_DIR "android")

# -------------------------------------------------------------------------------
elseif(${CMAKE_SYSTEM_NAME} MATCHES "Emscripten")

    set(BW_PLATFORM_UNIX       1)
    set(BW_PLATFORM_EMSCRIPTEN 1)
    set(BW_PLATFORM_DIR "web")

# -------------------------------------------------------------------------------
else()
    message(FATAL_ERROR "Unsupported operating system")
    return()
endif()