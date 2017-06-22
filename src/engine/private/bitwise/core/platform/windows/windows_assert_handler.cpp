#include <windows.h>
#include "bitwise/core/internal.h"
#include "bitwise/core/cstring.h"

namespace bw
{

// -----------------------------------------------------------------------------
//  Constants
// -----------------------------------------------------------------------------
static const size_t kAssertBufferLength = 1024;

// -----------------------------------------------------------------------------
//  Internal methods
// -----------------------------------------------------------------------------
void internal::default_assert_handler(const char* expression, const char* message, const char* file, int line, bool callstack, bool halt)
{
    char output[kAssertBufferLength];

    if (message != nullptr)
    {
        bw::cstring::format(output, kAssertBufferLength, "Assertion failed: ( {%s} )\nMessage: \"{%s}\"\nFile: {%s}:{%d}", expression, message, file, line);
    }
    else
    {
        bw::cstring::format(output, kAssertBufferLength, "Assertion failed: ( {%s} )\nFile: {%s}:{%d}", expression, file, line);
    }

    if (callstack)
    {
        // TODO
    }

	MessageBox(nullptr, output, "Bitwise Engine - Assertion failed!", MB_OK | MB_ICONERROR);

    // Check if execution should be halted
    if (halt)
    {
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
}

}	// namespace bw