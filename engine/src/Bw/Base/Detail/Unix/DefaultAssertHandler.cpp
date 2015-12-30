#include <csignal>
#include "Bw/Base/Detail/DefaultAssertHandler.h"
#include "Bw/Base/String.h"
#include "Bw/Base/System.h"

namespace bw
{

////////////////////////////////////////////////////////////////////////////////
//  Class std functions
////////////////////////////////////////////////////////////////////////////////
DefaultAssertHandler::DefaultAssertHandler()
{
}

////////////////////////////////////////////////////////////////////////////////
//  Public functions
////////////////////////////////////////////////////////////////////////////////
void DefaultAssertHandler::operator()(const char* exp, const char* file, int line)
{
    char args[512];

    bw::sprintf(args, 1024,
        "--error --title \"Bitwise Engine - Assertion failed!\" --text='Assertion failed: ( %s )\nFile: %s:%d'",
        exp, file, line);

    system::exec("/usr/bin/zenity", args);
    raise(SIGABRT);
}

}   // namespace bw