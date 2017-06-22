#include <Windows.h>
#include "bitwise/core/internal.h"
#include "bitwise/core/cstring.h"
#include "bitwise/core/callstack.h"

// -----------------------------------------------------------------------------
//  Constants
// -----------------------------------------------------------------------------
static const size_t kMaxOutputBuffer = 4096;

// -----------------------------------------------------------------------------
//  Private variables
// -----------------------------------------------------------------------------
static char m_outputBuffer[kMaxOutputBuffer];

namespace bw
{

// -----------------------------------------------------------------------------
//  Internal methods
// -----------------------------------------------------------------------------
void internal::assert::default_handler(const char* expression, const char* message, const char* file, int line, bool callstack, bool halt)
{
    size_t nbChars = bw::cstring::format(m_outputBuffer, kMaxOutputBuffer, "Assertion failed: ( %s )", expression);

    if (message != nullptr)
    {
        nbChars += bw::cstring::format(m_outputBuffer + nbChars, kMaxOutputBuffer - nbChars, "\nMessage: \"%s\"", message);
    }

    nbChars += bw::cstring::format(m_outputBuffer + nbChars, kMaxOutputBuffer - nbChars, "\nFile: %s:%d", file, line);

    if (callstack)
    {
        char callstackBuffer[4096];
        bw::callstack::to_string(callstackBuffer, 4096);
        nbChars += bw::cstring::format(m_outputBuffer + nbChars, kMaxOutputBuffer - nbChars, "\n\nCallstack:\n%s", callstackBuffer);
    }

	MessageBox(nullptr, m_outputBuffer, "Bitwise Engine - Assertion failed!", MB_OK | MB_ICONERROR);

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