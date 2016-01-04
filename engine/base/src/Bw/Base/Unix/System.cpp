#include <cstdlib>
#include <unistd.h>
#include "Bw/Base/System.h"
#include "Bw/Base/CharArray.h"

namespace bw
{

////////////////////////////////////////////////////////////////////////////////
//  Constants
////////////////////////////////////////////////////////////////////////////////
static const size_t kMaxCmdLength = 1024;

////////////////////////////////////////////////////////////////////////////////
//  Public functions
////////////////////////////////////////////////////////////////////////////////
int System::Execute(const char* program, const char* args)
{
    int status = -1;

    if (args)
    {
        char cmd[kMaxCmdLength];
        CharArray::Format(cmd, kMaxCmdLength, "%s %s", program, args);
        
        status = ::system(cmd);
    }
    else
    {
        status = ::system(program);
    }

    return status;
}

// -----------------------------------------------------------------------------

size_t System::GetPageSize()
{
    return ::sysconf(_SC_PAGE_SIZE);
}

}   // namespace bw