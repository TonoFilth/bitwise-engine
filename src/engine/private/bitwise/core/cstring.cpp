#include <cstdio>   // sscanf
#include <cstring>  // strcpy

#if defined(BW_PLATFORM_LINUX) || defined(BW_PLATFORM_WEB)
#   include <strings.h> // strcasecmp()
#endif

#include "bitwise/core/cstring.h"

namespace bw
{

////////////////////////////////////////////////////////////////////////////////
/// \details Detailed description.
/// \todo Write detailed description.
////////////////////////////////////////////////////////////////////////////////
bool cstring::contains(const char* str, const char needle)
{
    // Discard empty strings
    if (*str == '\0' || needle == '\0')
    {
        return false;
    }

    while (*str != '\0')
    {
        if (*str++ == needle)
        {
            return true;
        }
    }

    return false;
}

////////////////////////////////////////////////////////////////////////////////
/// \details Detailed description.
/// \todo Write detailed description.
////////////////////////////////////////////////////////////////////////////////
bool cstring::contains(const char* str, const char* needle)
{
    // Discard empty strings
    if (*str == '\0' || *needle == '\0')
    {
        return false;
    }

    const char* n = needle;

    while (*str != '\0' && *n != '\0')
    {
        n = (*str++ == *n ? n+1 : needle);
    }

    return *n == '\0';
}

////////////////////////////////////////////////////////////////////////////////
/// \details Detailed description.
/// \todo Write detailed description.
////////////////////////////////////////////////////////////////////////////////
bool cstring::starts_with(const char* str, const char needle)
{
    return (*str != '\0' && needle != '\0' && *str == needle);
}

////////////////////////////////////////////////////////////////////////////////
/// \details Detailed description.
/// \todo Write detailed description.
////////////////////////////////////////////////////////////////////////////////
bool cstring::starts_with(const char* str, const char* needle)
{
    // Discard empty strings
    if (*str == '\0' || *needle == '\0')
    {
        return false;
    }

    const char* n = needle;

    while (*str != '\0' && *n != '\0')
    {
        if (*str++ != *n++)
        {
            return false;
        }
    }

    return *n == '\0';
}

////////////////////////////////////////////////////////////////////////////////
/// \details Detailed description.
/// \todo Write detailed description.
////////////////////////////////////////////////////////////////////////////////
bool cstring::ends_with(const char* str, const char needle)
{
    // Discard empty strings
    if (*str == '\0' || needle == '\0')
    {
        return false;
    }

    while (*(str+1) != '\0')
    {
        ++str;
    }
    
    return *str == needle;
}

////////////////////////////////////////////////////////////////////////////////
/// \details Detailed description.
/// \todo Write detailed description.
////////////////////////////////////////////////////////////////////////////////
bool cstring::ends_with(const char* str, const char* needle)
{
    // Discard empty strings
    if (*str == '\0' || *needle == '\0')
    {
        return false;
    }

    const char* s = str;
    const char* n = needle;

    while (*(s+1) != '\0') ++s;
    while (*(n+1) != '\0') ++n;

    while (s >= str && n >= needle)
    {
        if (*s-- != *n--)
        {
            return false;
        }
    }

    return *n == '\0';
}

////////////////////////////////////////////////////////////////////////////////
/// \details Detailed description.
/// \todo Write detailed description.
////////////////////////////////////////////////////////////////////////////////
bool cstring::replace(char* str, char needle, char replacement)
{
    bool replaced = false;

    while (*str != '\0')
    {
        if (*str == needle)
        {
            *str = replacement;
            replaced = true;
        }

        ++str;
    }

    return replaced;
}

////////////////////////////////////////////////////////////////////////////////
/// \details Detailed description.
/// \todo Write detailed description.
////////////////////////////////////////////////////////////////////////////////
size_t cstring::format(char* buffer, size_t bufferSize, const char* format, ...)
{
	va_list args;
	va_start(args, format);

	size_t nbChars = bw::cstring::format_va_list(buffer, bufferSize, format, args);
	
	va_end(args);

	return nbChars;
}

////////////////////////////////////////////////////////////////////////////////
/// \details Detailed description.
/// \todo Write detailed description.
////////////////////////////////////////////////////////////////////////////////
size_t cstring::truncated_format(char* buffer, size_t bufferSize, const char* format, ...)
{
	va_list args;
	va_start(args, format);

	size_t nbChars = cstring::truncated_format_va_list(buffer, bufferSize, format, args);
	
	va_end(args);

	return nbChars;
}

////////////////////////////////////////////////////////////////////////////////
/// \details Detailed description.
/// \todo Write detailed description.
////////////////////////////////////////////////////////////////////////////////
size_t bw::cstring::scan_format(const char* str, const char* format, ...)
{
    va_list args;
	va_start(args, format);

	size_t nbChars = bw::cstring::scan_format_va_list(str, format, args);
	
	va_end(args);

	return nbChars;
}

////////////////////////////////////////////////////////////////////////////////
/// \details Detailed description.
/// \todo Write detailed description.
////////////////////////////////////////////////////////////////////////////////
size_t cstring::length(const char* str)
{
    return ::strlen(str);
}

}	// namespace bw