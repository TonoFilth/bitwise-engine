#include <cstdio>
#include "Bw/Base/Console.h"
#include "Bw/Base/CharArray.h"

namespace bw
{

////////////////////////////////////////////////////////////////////////////////
//  Public functions
////////////////////////////////////////////////////////////////////////////////
void Console::Write(const char* str)
{
	::fputs(str, stdout);
}

// -----------------------------------------------------------------------------

void Console::WriteLine(const char* str)
{
	::puts(str);
}

// -----------------------------------------------------------------------------

void Console::WriteFormat(const char* fmt, ...)
{
	va_list args;
	va_start(args, fmt);

	char formattedOutput[512];
	
	int nbChars = CharArray::FormatVA(formattedOutput, 512, fmt, args);

	::fputs(formattedOutput, stdout);
	
	va_end(args);
}

}	// namespace bw