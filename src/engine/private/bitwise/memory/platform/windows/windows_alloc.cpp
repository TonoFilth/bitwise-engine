#include <Windows.h>
#include "bitwise/core/assert.h"
#include "bitwise/core/system.h"
#include "bitwise/core/cstring.h"
#include "bitwise/memory/internal.h"

namespace bw
{

// -----------------------------------------------------------------------------
//  Internal functions
// -----------------------------------------------------------------------------
void* memory::alloc(size_t sizeBytes)
{
    // Make sure sizeBytes is multiple of system page size
    BW_ASSERT(sizeBytes % system::page_size() == 0, "sizeBytes ({0}) is not a multiple of the page size ({1})", sizeBytes, system::page_size());

	return VirtualAlloc(nullptr, sizeBytes, MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);
}

// -----------------------------------------------------------------------------

void memory::free(void* data, size_t sizeBytes)
{
    // Make sure sizeBytes is multiple of system page size
	BW_ASSERT(sizeBytes % system::page_size() == 0, "sizeBytes ({0}) is not a multiple of the page size ({1})", sizeBytes, system::page_size());

	VirtualFree(data, sizeBytes, MEM_RELEASE);
}

}	// namespace bw