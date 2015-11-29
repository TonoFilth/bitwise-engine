#ifndef BW_BASE_STRING_H
#define BW_BASE_STRING_H

#include <cstdio>
#include <cstring>
#include <cstdarg>
#if defined(BW_SYSTEM_LINUX)
#   include <strings.h> // strcasecmp()
#endif

#include "Bw/Base/Common/Module.h"

namespace bw
{

BW_INLINE BW_BASE_API void strcpy(char* dest, size_t size, const char* src);
BW_INLINE BW_BASE_API void strcat(char* dest, size_t size, const char* src);
BW_INLINE BW_BASE_API i32_t stricmp(const char* str1, const char* str2);
BW_INLINE BW_BASE_API i32_t sprintf(char* dest, size_t size, const char* fmt, ...);
BW_INLINE BW_BASE_API i32_t vsprintf(char* dest, size_t size, const char* fmt, va_list args);

////////////////////////////////////////////////////////////////////////////////
// Include system definitions
////////////////////////////////////////////////////////////////////////////////
#if defined(BW_SYSTEM_WINDOWS)
#	include "Bw/Base/_detail/Windows/String.inl"
#elif defined(BW_SYSTEM_LINUX)
#	include "Bw/Base/_detail/Unix/String.inl"
#endif

}	// namespace bw

#endif	// BW_BASE_STRING_H