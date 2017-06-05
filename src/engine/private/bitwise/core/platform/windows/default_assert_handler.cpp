#include <windows.h>
#include "bitwise/core/default_assert_handler.h"
#include "bitwise/core/cstring.h"

namespace bw
{

// -----------------------------------------------------------------------------
//  Constructors & destructors
// -----------------------------------------------------------------------------
DefaultAssertHandler::DefaultAssertHandler()
{
}

// -----------------------------------------------------------------------------

DefaultAssertHandler::~DefaultAssertHandler()
{
}

// -----------------------------------------------------------------------------
//  Public methods
// -----------------------------------------------------------------------------
void DefaultAssertHandler::operator()(const char* exp, const char* file, int line)
{
	char message[512];

	cstring::format(message, 512, "Assertion failed: ( %s )\nFile: %s:%d", exp, file, line);
	MessageBox(nullptr, message, "Bitwise Engine - Assertion failed!", MB_OK | MB_ICONERROR);

	// Trigger a breakpoint and let the debugger take control
	// If no debugger is attached, stop the execution
	if (IsDebuggerPresent())
	{
		DebugBreak();
	}
	else
	{
		FatalExit(0);
	}
}

}	// namespace bw