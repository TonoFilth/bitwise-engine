#ifndef BW_BASE_CHAR_ARRAY_H
#define BW_BASE_CHAR_ARRAY_H

#include "Bw/Base/Export.h"

#include <cstdio>
#include <cstring>
#if defined(BW_SYSTEM_ANDROID)
	#include <stdarg.h>	// va_list
#else
	#include <cstdarg>	// va_list
#endif

#if defined(BW_SYSTEM_LINUX) || defined(BW_SYSTEM_WEB)
#   include <strings.h> // strcasecmp()
#endif

namespace bw
{
namespace CharArray
{

////////////////////////////////////////////////////////////////////////////////
//  Public functions
////////////////////////////////////////////////////////////////////////////////
BW_INLINE BW_BASE_API void Copy            (char* dest, size_t size, const char* src);
BW_INLINE BW_BASE_API void Concatenate     (char* dest, size_t size, const char* src);
BW_INLINE BW_BASE_API int  Format          (char* dest, size_t size, const char* fmt, ...);
BW_INLINE BW_BASE_API int  FormatVA        (char* dest, size_t size, const char* fmt, va_list args);
BW_INLINE BW_BASE_API bool Equals          (const char* str1, const char* str2);
BW_INLINE BW_BASE_API bool EqualsIgnoreCase(const char* str1, const char* str2);

}	// namespace CharArray
}	// namespace bw

#if defined(BW_SYSTEM_WINDOWS)
#	include "Bw/Base/Windows/CharArray.inl"
#elif defined(BW_SYSTEM_WEB)
#	include "Bw/Base/Web/CharArray.inl"
#else
#	error "TODO"
#endif

#endif	// BW_BASE_CHAR_ARRAY_H