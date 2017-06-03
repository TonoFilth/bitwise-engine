#include <cstdlib>
#include <unistd.h>
#include "bitwise/core/platform.h"
#include "bitwise/core/cstring.h"

namespace bw
{

// -----------------------------------------------------------------------------
//  Constants
// -----------------------------------------------------------------------------
static const size_t MAX_CMD_LENGTH = 1024;

// -----------------------------------------------------------------------------
//  Public functions
// -----------------------------------------------------------------------------
int platform::exec(const char* program, const char* args)
{
    int status = -1;

    if (args)
    {
        char cmd[MAX_CMD_LENGTH];
        cstring::format(cmd, MAX_CMD_LENGTH, "%s %s", program, args);
        
        status = ::system(cmd);
    }
    else
    {
        status = ::system(program);
    }

    return status;
}

// -----------------------------------------------------------------------------

size_t platform::page_size()
{
    return ::sysconf(_SC_PAGE_SIZE);
}

}   // namespace bw