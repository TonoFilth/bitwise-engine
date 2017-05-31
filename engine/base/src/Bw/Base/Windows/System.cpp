#include <Windows.h>
#include "Bw/Base/System.h"

namespace bw
{

////////////////////////////////////////////////////////////////////////////////
//  Public functions
////////////////////////////////////////////////////////////////////////////////
int System::Execute(const char* program, const char* args)
{
	return -1;
}

// -----------------------------------------------------------------------------

size_t System::GetPageSize()
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