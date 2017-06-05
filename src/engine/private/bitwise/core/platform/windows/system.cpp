#include <Windows.h>
#include "bitwise/core/system.h"
#include "bitwise/core/backtrace.h"

namespace bw
{

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

StackFrame* system::backtrace(int skip)
{
	return nullptr;
}

// -----------------------------------------------------------------------------

void system::print_backtrace(StackFrame* frame)
{
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