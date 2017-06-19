#include <Windows.h>
#include "bitwise/core/system.h"
#include "bitwise/core/internal.h"
#include "bitwise/core/assert.h"

namespace bw
{

// -----------------------------------------------------------------------------
//  Internal functions
// -----------------------------------------------------------------------------
void system::initialize(int argc, char** argv)
{
}

// -----------------------------------------------------------------------------

void system::shutdown()
{
}

// -----------------------------------------------------------------------------
//  Public functions
// -----------------------------------------------------------------------------
int system::exec(const char* program, const char* args)
{
	return -1;
}

// -----------------------------------------------------------------------------

size_t system::page_size()
{
    SYSTEM_INFO info;
	GetSystemInfo(&info);

	return info.dwPageSize;
}

// -----------------------------------------------------------------------------

//size_t System::GetCacheSize()
//{
//	SYSTEM_LOGICAL_PROCESSOR_INFORMATION info[16];
//	DWORD nbProcessors = 608;
//
//	if (GetLogicalProcessorInformation(info, &nbProcessors))
//	{
//		return 1;
//	}
//	else
//	{
//		return 0;
//	}
//}

}	// namespace bw