#include <cstdio>
#include "bitwise/core/console.h"
#include "bitwise/core/cstring.h"

namespace bw
{

// -----------------------------------------------------------------------------
//  Public functions
// -----------------------------------------------------------------------------
void console::write(const char* str)
{
	::fputs(str, stdout);
}

// -----------------------------------------------------------------------------

void console::write_line(const char* str)
{
	::puts(str);
}

// -----------------------------------------------------------------------------

void console::write_format(const char* fmt, ...)
{
	va_list args;
	va_start(args, fmt);

	char formattedOutput[512];
	
	int nbChars = cstring::format_va(formattedOutput, 512, fmt, args);

	::fputs(formattedOutput, stdout);
	
	va_end(args);
}

}	// namespace bw