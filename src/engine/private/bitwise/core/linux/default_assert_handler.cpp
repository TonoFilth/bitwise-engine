#include <csignal>
#include "bitwise/core/default_assert_handler.h"
#include "bitwise/core/cstring.h"
#include "bitwise/core/platform.h"
#include "bitwise/core/backtrace.h"

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
    char args[4096];
    char stack_trace[2048];
    int size = 2048;
    char* p = stack_trace;

    StackFrame* firstFrame = platform::backtrace(2);
    StackFrame* frame = firstFrame;

    int count = 0;

    while (frame != nullptr && size > 0)
    {
        int nbChars = cstring::format(p, size, "#%d | %s in %s:%u", count, frame->function, frame->filename, frame->line);
        
        p += nbChars;
        size -= nbChars;
        ++count;

        *p = (frame->next != nullptr ? '\n' : '\0');
        p++;
        frame = frame->next;
    }

    cstring::format(args, 4096,
        "--error --title \"Bitwise Engine - Assertion failed!\" --text=\"Assertion failed: ( %s )\nFile: %s:%d\n\nStack Trace:\n\n%s\"",
        exp, file, line, stack_trace);

    platform::exec("/usr/bin/zenity", args);
    platform::exec("xdg-open ", firstFrame->filename);

    raise(SIGABRT);
}

}   // namespace bw