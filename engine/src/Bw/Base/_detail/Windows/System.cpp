#include <cstdlib>
#include <Windows.h>
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

	// Not implemented
	BW_ASSERT(0);

    return status;
}

// -----------------------------------------------------------------------------

size_t system::get_page_size()
{
	SYSTEM_INFO sysInfo;
	GetSystemInfo(&sysInfo);

	return sysInfo.dwPageSize;
}

}   // namespace bw