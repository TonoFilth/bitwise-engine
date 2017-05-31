#include <cstdio>
#include <cstdarg>
#include <Windows.h>
#include "Bw/Base/Console.h"
#include "Bw/Base/CString.h"

namespace bw
{

////////////////////////////////////////////////////////////////////////////////
//  Public functions
////////////////////////////////////////////////////////////////////////////////
void Console::Write(const char* str)
{
#if defined(BW_DEBUG)
	OutputDebugString(str);
#endif

	::fputs(str, stdout);
}

// -----------------------------------------------------------------------------

void Console::WriteLine(const char* str)
{
#if defined(BW_DEBUG)
	OutputDebugString(str);
	OutputDebugString("\n");
#endif

	::puts(str);
}

// -----------------------------------------------------------------------------

void Console::WriteFormat(const char* fmt, ...)
{
	va_list args;
	va_start(args, fmt);

	char formattedOutput[512];
	
	int nbChars = CString::FormatVA(formattedOutput, 512, fmt, args);

#if defined(BW_DEBUG)
	OutputDebugString(formattedOutput);
#endif

	::fputs(formattedOutput, stdout);
	
	va_end(args);
}

}	// namespace bw