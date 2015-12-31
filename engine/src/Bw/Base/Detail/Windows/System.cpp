#include <cstdlib>
#include <Windows.h>
#include "Bw/Base/Common/System.h"
#include "Bw/Base/Common/String.h"
#include "Bw/Base/Common/Assert.h"

namespace bw
{

////////////////////////////////////////////////////////////////////////////////
//  Public functions
////////////////////////////////////////////////////////////////////////////////
int32_t System::Exec(const char* program, const char* args)
{
    int32_t status = -1;

	// Not implemented
	BW_ASSERT(0);

    return status;
}

// -----------------------------------------------------------------------------

size_t System::GetPageSize()
{
	SYSTEM_INFO sysInfo;
	GetSystemInfo(&sysInfo);

	return sysInfo.dwPageSize;
}

}   // namespace bw