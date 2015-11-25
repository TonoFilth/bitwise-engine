#ifndef BW_BASE_DEFAULT_ASSERT_HANDLER_H
#define BW_BASE_DEFAULT_ASSERT_HANDLER_H

#include <csignal>
#include "Bw/Base/Common/ModuleTypes.h"
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

#endif  // BW_BASE_DEFAULT_ASSERT_HANDLER_H