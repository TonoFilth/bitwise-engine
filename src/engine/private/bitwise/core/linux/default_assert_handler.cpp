#include <csignal>
#include "bitwise/core/default_assert_handler.h"
#include "bitwise/core/cstring.h"
#include "bitwise/core/platform.h"

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
    char args[512];

    cstring::format(args, 512,
        "--error --title \"Bitwise Engine - Assertion failed!\" --text='Assertion failed: ( %s )\nFile: %s:%d'",
        exp, file, line);

    platform::exec("/usr/bin/zenity", args);
    raise(SIGABRT);
}

}   // namespace bw