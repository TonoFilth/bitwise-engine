#include <cstdio>
#include <Windows.h>

#include "bitwise/core/console.h"
#include "bitwise/core/cstring.h"

// -----------------------------------------------------------------------------
//  Constants
// -----------------------------------------------------------------------------
static const size_t kMaxFormatMessage = 4096;

// -----------------------------------------------------------------------------
//  Private variables
// -----------------------------------------------------------------------------
static char m_formatMessage[kMaxFormatMessage];

namespace bw
{

////////////////////////////////////////////////////////////////////////////////
/// \details Detailed description.
/// \todo Write detailed description.
////////////////////////////////////////////////////////////////////////////////
void console::write(const char* str)
{
#if defined(BW_DEBUG)
	OutputDebugString(str);
#endif

	::fputs(str, stdout);
}

////////////////////////////////////////////////////////////////////////////////
/// \details Detailed description.
/// \todo Write detailed description.
////////////////////////////////////////////////////////////////////////////////
void console::write_line(const char* str)
{
#if defined(BW_DEBUG)
	OutputDebugString(str);
	OutputDebugString("\n");
#endif

	::puts(str);
    ::puts("\n");
}

////////////////////////////////////////////////////////////////////////////////
/// \details Detailed description.
/// \todo Write detailed description.
////////////////////////////////////////////////////////////////////////////////
void console::write_format(const char* format, ...)
{
	va_list args;
	va_start(args, format);

	int nbChars = bw::cstring::format_va_list(m_formatMessage, kMaxFormatMessage, format, args);

#if defined(BW_DEBUG)
	OutputDebugString(m_formatMessage);
#endif

	::fputs(m_formatMessage, stdout);
	
	va_end(args);
}

}	// namespace bw