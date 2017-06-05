#pragma once

#include "bitwise/core/export.h"

#include <cstdio>
#include <cstring>
#if defined(BW_PLATFORM_ANDROID)
    #include <stdarg.h> // va_list
#else
    #include <cstdarg>  // va_list
#endif

#if defined(BW_PLATFORM_LINUX) || defined(BW_PLATFORM_WEB)
#   include <strings.h> // strcasecmp()
#endif

namespace bw
{
namespace cstring
{

// -----------------------------------------------------------------------------
//  Public functions
// -----------------------------------------------------------------------------
BW_INLINE BW_API void copy              (char* dest, size_t size, const char* src);
BW_INLINE BW_API void concatenate       (char* dest, size_t size, const char* src);
BW_INLINE BW_API int  format            (char* dest, size_t size, const char* fmt, ...);
BW_INLINE BW_API int  format_va         (char* dest, size_t size, const char* fmt, va_list args);
BW_INLINE BW_API bool equals            (const char* str1, const char* str2);
BW_INLINE BW_API bool equals_ignore_case(const char* str1, const char* str2);

}   // namespace cstring
}   // namespace bw

// -----------------------------------------------------------------------------
//  Platform implementation
// -----------------------------------------------------------------------------
#if defined(BW_PLATFORM_WINDOWS)
#   include "bitwise/core/platform/windows/cstring.inl"
#else
#   include "bitwise/core/platform/unix/cstring.inl"
#endif