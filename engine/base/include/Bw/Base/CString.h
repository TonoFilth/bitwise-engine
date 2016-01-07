#ifndef BW_BASE_CSTRING_H
#define BW_BASE_CSTRING_H

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
namespace CString
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

}	// namespace CString
}	// namespace bw

////////////////////////////////////////////////////////////////////////////////
//  System specific implementation
////////////////////////////////////////////////////////////////////////////////
#if defined(BW_SYSTEM_WINDOWS)
#	include "Bw/Base/Windows/CString.inl"
#else
#	include "Bw/Base/Unix/CString.inl"
#endif

#endif	// BW_BASE_CSTRING_H