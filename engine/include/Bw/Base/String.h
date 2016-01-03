#ifndef BW_BASE_STRING_H
#define BW_BASE_STRING_H

#include "Bw/Base/Common/Export.h"
#include "Bw/Base/Common/Types.h"

#include <cstdio>
#include <cstring>
#if defined(BW_SYSTEM_ANDROID)
	#include <stdarg.h>	// va_list
#else
	#include <cstdarg>	// va_list
#endif

#if defined(BW_SYSTEM_LINUX)
#   include <strings.h> // strcasecmp()
#endif

namespace bw
{

BW_INLINE BW_BASE_API void    Strcpy(char* dest, size_t size, const char* src);
BW_INLINE BW_BASE_API void    Strcat(char* dest, size_t size, const char* src);
BW_INLINE BW_BASE_API int32_t Stricmp(const char* str1, const char* str2);
BW_INLINE BW_BASE_API int32_t Sprintf(char* dest, size_t size, const char* fmt, ...);
BW_INLINE BW_BASE_API int32_t Vsprintf(char* dest, size_t size, const char* fmt, va_list args);

}	// namespace bw

////////////////////////////////////////////////////////////////////////////////
// Include system definitions
////////////////////////////////////////////////////////////////////////////////
#if defined(BW_SYSTEM_WINDOWS)
#	include "Bw/Base/Detail/Windows/String.inl"
#elif defined(BW_SYSTEM_LINUX)
#	include "Bw/Base/Detail/Unix/String.inl"
#endif

#endif	// BW_BASE_STRING_H