#include <cerrno>   // errno
#include <cstdio>   // sscanf
#include <cstring>  // strcpy

#include "bitwise/core/cstring.h"

namespace bw
{

////////////////////////////////////////////////////////////////////////////////
/// \details Detailed description.
/// \todo Write detailed description.
////////////////////////////////////////////////////////////////////////////////
void cstring::copy(char* buffer, size_t bufferSize, const char* str)
{
    ::strcpy_s(buffer, bufferSize, str);
}

////////////////////////////////////////////////////////////////////////////////
/// \details Detailed description.
/// \todo Write detailed description.
////////////////////////////////////////////////////////////////////////////////
void cstring::concatenate(char* buffer, size_t bufferSize, const char* str)
{
	::strcat_s(buffer, bufferSize, str);
}

////////////////////////////////////////////////////////////////////////////////
/// \details Detailed description.
/// \todo Write detailed description.
////////////////////////////////////////////////////////////////////////////////
bool cstring::equals(const char* str1, const char* str2)
{
	return ::strcmp(str1, str2) == 0;
}

////////////////////////////////////////////////////////////////////////////////
/// \details Detailed description.
/// \todo Write detailed description.
////////////////////////////////////////////////////////////////////////////////
bool cstring::equals_ignore_case(const char* str1, const char* str2)
{
	return ::_stricmp(str1, str2) == 0;
}

////////////////////////////////////////////////////////////////////////////////
/// \details Detailed description.
/// \todo Write detailed description.
////////////////////////////////////////////////////////////////////////////////
size_t cstring::format_va_list(char* buffer, size_t bufferSize, const char* format, va_list args)
{
	int nbChars = ::vsprintf_s(buffer, bufferSize, format, args);

    return nbChars >= 0 ? nbChars : 0;
}

////////////////////////////////////////////////////////////////////////////////
/// \details Detailed description.
/// \todo Write detailed description.
////////////////////////////////////////////////////////////////////////////////
size_t bw::cstring::scan_format_va_list(const char* str, const char* format, va_list args)
{
    int nbAssignedFields = ::vsscanf_s(str, format, args);

    if (nbAssignedFields != EOF)
    {
        return nbAssignedFields;
    }

    // Handle error

    return 0;
}

////////////////////////////////////////////////////////////////////////////////
/// \details Detailed description.
/// \todo Write detailed description.
////////////////////////////////////////////////////////////////////////////////
void cstring::truncated_copy(char* buffer, size_t bufferSize, const char* str)
{
    ::strncpy_s(buffer, bufferSize, str, bufferSize-1);
}

////////////////////////////////////////////////////////////////////////////////
/// \details Detailed description.
/// \todo Write detailed description.
////////////////////////////////////////////////////////////////////////////////
void cstring::truncated_concatenate(char* buffer, size_t bufferSize, const char* str)
{
	::strncat_s(buffer, bufferSize, str, _TRUNCATE);
}

////////////////////////////////////////////////////////////////////////////////
/// \details Detailed description.
/// \todo Write detailed description.
////////////////////////////////////////////////////////////////////////////////
size_t cstring::truncated_format_va_list(char* buffer, size_t bufferSize, const char* format, va_list args)
{
	int nbChars = ::vsnprintf_s(buffer, bufferSize, _TRUNCATE, format, args);
    
    return nbChars >= 0 ? nbChars : (errno == 0 ? bw::cstring::length(buffer) : 0);
}

}	// namespace bw