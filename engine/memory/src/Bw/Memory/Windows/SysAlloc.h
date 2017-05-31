#ifndef BW_MEMORY_SYSALLOC_H
#define BW_MEMORY_SYSALLOC_H

#include <Windows.h>
#include "Bw/Base/Assert.h"
#include "Bw/Base/Macros.h"
#include "Bw/Base/System.h"

namespace bw
{
namespace Internal
{

////////////////////////////////////////////////////////////////////////////////
//	Public functions
////////////////////////////////////////////////////////////////////////////////
BW_INLINE void* SysAlloc(size_t sizeBytes)
{
	// Make sure sizeBytes is multiple of system page size
	BW_ASSERT(sizeBytes % System::GetPageSize() == 0);

	return VirtualAlloc(nullptr, sizeBytes, MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);
}

// -----------------------------------------------------------------------------

BW_INLINE void SysFree(void* data, size_t sizeBytes)
{
	// Make sure sizeBytes is multiple of system page size
	BW_ASSERT(sizeBytes % System::GetPageSize() == 0);

	VirtualFree(data, sizeBytes, MEM_RELEASE);
}

}	// namespace Internal
}	// namespace bw

#endif	// BW_MEMORY_SYSALLOC_H