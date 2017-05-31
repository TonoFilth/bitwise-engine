#include <csignal>
#include "Bw/Base/DefaultAssertHandler.h"
#include "Bw/Base/CString.h"
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

    CString::Format(args, 512,
        "--error --title \"Bitwise Engine - Assertion failed!\" --text='Assertion failed: ( %s )\nFile: %s:%d'",
        exp, file, line);

    System::Execute("/usr/bin/zenity", args);
    System::GetPageSize();
    raise(SIGABRT);
}

}   // namespace bw