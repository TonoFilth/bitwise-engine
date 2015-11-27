#include <cstdlib>
#include <unistd.h>
#include "Bw/Base/System.h"
#include "Bw/Base/String.h"

namespace
{

////////////////////////////////////////////////////////////////////////////////
//  Constants
////////////////////////////////////////////////////////////////////////////////
const size_t kMaxCmdLength = 1024;

}   // private namespace

namespace bw
{

////////////////////////////////////////////////////////////////////////////////
//  Public functions
////////////////////////////////////////////////////////////////////////////////
I32 system::exec(const char* program, const char* args)
{
    I32 status = -1;

    if (args)
    {
        char cmd[kMaxCmdLength];
        bw::sprintf(cmd, kMaxCmdLength, "%s %s", program, args);
        
        status = ::system(cmd);
    }
    else
    {
        status = ::system(program);
    }

    return status;
}

// -----------------------------------------------------------------------------

size_t system::get_page_size()
{
    return ::sysconf(_SC_PAGE_SIZE);
}

}   // namespace bw