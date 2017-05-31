# ===============================================================================
#   Macro to help define options
# ===============================================================================
macro(bw_option var default type helpstr)
    if(NOT DEFINED ${var})
        set(${var} ${default})
    endif()
    set(${var} ${${var}} CACHE ${type} ${helpstr} FORCE)
endmacro()