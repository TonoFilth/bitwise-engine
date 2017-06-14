#include <cstdio>
#include <cstdarg>
#include <Windows.h>

#include "bitwise/core/console.h"
#include "bitwise/core/cstring.h"

namespace bw
{

////////////////////////////////////////////////////////////////////////////////
//  Public functions
////////////////////////////////////////////////////////////////////////////////
void console::write(const char* str)
{
#if defined(BW_DEBUG)
	OutputDebugString(str);
#endif

	::fputs(str, stdout);
}

// -----------------------------------------------------------------------------

void console::write_line(const char* str)
{
#if defined(BW_DEBUG)
	OutputDebugString(str);
	OutputDebugString("\n");
#endif

	::puts(str);
}

// -----------------------------------------------------------------------------

void console::write_cformat(const char* fmt, ...)
{
	va_list args;
	va_start(args, fmt);

	char formattedOutput[512];
	
	int nbChars = cstring::cformat_va(formattedOutput, 512, fmt, args);

#if defined(BW_DEBUG)
	OutputDebugString(formattedOutput);
#endif

	::fputs(formattedOutput, stdout);
	
	va_end(args);
}

}	// namespace bw