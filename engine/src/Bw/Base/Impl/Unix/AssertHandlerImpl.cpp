#include <csignal>
#include <cstdio>
#include "Bw/Base/Impl/Unix/AssertHandlerImpl.h"

namespace bw
{

////////////////////////////////////////////////////////////////////////////////
//  Class std functions
////////////////////////////////////////////////////////////////////////////////
AssertHandlerImpl::AssertHandlerImpl()
{
}

////////////////////////////////////////////////////////////////////////////////
//  Public functions
////////////////////////////////////////////////////////////////////////////////
void AssertHandlerImpl::operator()(const char* exp, const char* file, int line)
{
    fprintf(stderr, "Assertion failed: %s at %s:%d\n", exp, file, line);
    fflush(stderr);

    // Trigger a breakpoint and let the debugger take control
    // If no debugger is attached, stop the execution
    raise(SIGABRT);
}

}   // namespace bw