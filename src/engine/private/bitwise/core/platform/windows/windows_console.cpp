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

// -----------------------------------------------------------------------------
//  Private functions
// -----------------------------------------------------------------------------
static void console_write(const char* str, FILE* stream)
{
	::fputs(str, stream);
	::fflush(stream);

#if defined(BW_DEBUG)
	OutputDebugString(str);
#endif
}

// -----------------------------------------------------------------------------

static void console_write_line(const char* str, FILE* stream)
{
	::fputs(str, stream);
	::fputs("\n", stream);
	::fflush(stream);

#if defined(BW_DEBUG)
	OutputDebugString(str);
	OutputDebugString("\n");
#endif
}

// -----------------------------------------------------------------------------

static void console_write_format(const char* format, va_list args, FILE* stream)
{
	int nbChars = bw::cstring::format_va_list(m_formatMessage, kMaxFormatMessage, format, args);

	::fputs(m_formatMessage, stream);
	::fflush(stream);

#if defined(BW_DEBUG)
	OutputDebugString(m_formatMessage);
#endif
}

namespace bw
{

// -----------------------------------------------------------------------------
//  Public functions
// -----------------------------------------------------------------------------
void console::write(const char* str)
{
	console_write(str, stdout);
}

// -----------------------------------------------------------------------------

void console::write_line(const char* str)
{
	console_write_line(str, stdout);
}

// -----------------------------------------------------------------------------

void console::write_format(const char* format, ...)
{
	va_list args;
	va_start(args, format);

	console_write_format(format, args, stdout);
	
	va_end(args);
}

// -----------------------------------------------------------------------------

void console::error::write(const char* str)
{
	console_write(str, stderr);
}

// -----------------------------------------------------------------------------

void console::error::write_line(const char* str)
{
	console_write_line(str, stderr);
}

// -----------------------------------------------------------------------------

void console::error::write_format(const char* format, ...)
{
	va_list args;
	va_start(args, format);

	console_write_format(format, args, stderr);
	
	va_end(args);
}

}	// namespace bw