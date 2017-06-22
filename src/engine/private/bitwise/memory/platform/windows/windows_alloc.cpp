#include <Windows.h>
#include "bitwise/core/assert.h"
#include "bitwise/core/system.h"
#include "bitwise/log.h"
#include "bitwise/core/internal.h"
#include "bitwise/memory/internal.h"

namespace bw
{
// -----------------------------------------------------------------------------
//  Internal functions
// -----------------------------------------------------------------------------
void* internal::memory::valloc(size_t sizeBytes)
{
    // Make sure sizeBytes is multiple of system page size
    BW_ASSERT(sizeBytes % bw::system::page_size() == 0, "sizeBytes %zu is not a multiple of the page size %zu", sizeBytes, bw::system::page_size());

	return ::VirtualAlloc(nullptr, sizeBytes, MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);
}

// -----------------------------------------------------------------------------

void internal::memory::vfree(void* memory, size_t sizeBytes)
{
    // Make sure sizeBytes is multiple of system page size
	BW_ASSERT(sizeBytes % bw::system::page_size() == 0, "sizeBytes %zu is not a multiple of the page size %zu", sizeBytes, bw::system::page_size());

	::VirtualFree(memory, sizeBytes, MEM_RELEASE);
}

// -----------------------------------------------------------------------------

void* bw::internal::memory::malloc(size_t sizeBytes, size_t alignment)
{
    return _aligned_malloc(sizeBytes, alignment);
}

// -----------------------------------------------------------------------------

void bw::internal::memory::mfree(void* memory)
{
    _aligned_free(memory);
}

}	// namespace bw