#ifndef BW_MEMORY_SYSALLOC_H
#define BW_MEMORY_SYSALLOC_H

#include <sys/mman.h>
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

	return ::mmap(0, sizeBytes, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
}

// -----------------------------------------------------------------------------

BW_INLINE void SysFree(void* data, size_t sizeBytes)
{
	// Make sure sizeBytes is multiple of system page size
	BW_ASSERT(sizeBytes % System::GetPageSize() == 0);

	::munmap(data, sizeBytes);
}

}	// namespace Internal
}	// namespace bw

#endif	// BW_MEMORY_SYSALLOC_H