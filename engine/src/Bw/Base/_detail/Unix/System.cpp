#include <cstdlib>
#include "Bw/Base/System.h"
#include "Bw/Base/String.h"

namespace bw
{

////////////////////////////////////////////////////////////////////////////////
//  Constants
////////////////////////////////////////////////////////////////////////////////
const size_t BW_C_MAX_CMD_LENGTH = 1024;

////////////////////////////////////////////////////////////////////////////////
//  Public functions
////////////////////////////////////////////////////////////////////////////////
I32 system::exec(const char* program, const char* args)
{
    I32 status = -1;

    if (args)
    {
        char cmd[BW_C_MAX_CMD_LENGTH];
        bw::sprintf(cmd, BW_C_MAX_CMD_LENGTH, "%s %s", program, args);
        
        status = ::system(cmd);
    }
    else
    {
        status = ::system(program);
    }

    return status;
}

}   // namespace bw