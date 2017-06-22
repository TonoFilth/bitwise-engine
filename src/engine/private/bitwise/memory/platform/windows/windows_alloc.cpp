#include <Windows.h>
#include "bitwise/core/assert.h"
#include "bitwise/core/system.h"
#include "bitwise/core/cstring.h"
#include "bitwise/log.h"
#include "bitwise/core/internal.h"
#include "bitwise/memory/internal.h"

namespace bw
{

// -----------------------------------------------------------------------------
//  Internal functions
// -----------------------------------------------------------------------------
void* memory::alloc(size_t sizeBytes)
{
    // Make sure sizeBytes is multiple of system page size
    BW_ASSERT(sizeBytes % system::page_size() == 0, "sizeBytes %zu is not a multiple of the page size %zu", sizeBytes, system::page_size());

	return ::VirtualAlloc(nullptr, sizeBytes, MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);
}

// -----------------------------------------------------------------------------

void memory::free(void* memory, size_t sizeBytes)
{
    // Make sure sizeBytes is multiple of system page size
	BW_ASSERT(sizeBytes % system::page_size() == 0, "sizeBytes %zu is not a multiple of the page size %zu", sizeBytes, system::page_size());

	::VirtualFree(memory, sizeBytes, MEM_RELEASE);
}

// -----------------------------------------------------------------------------

void memory::save_size(PageAllocator& allocator, void* memory, size_t size)
{
}

// -----------------------------------------------------------------------------

void memory::delete_size(PageAllocator& allocator, void* memory)
{
}
    
// -----------------------------------------------------------------------------

size_t memory::size(const PageAllocator& allocator, void* memory)
{
    MEMORY_BASIC_INFORMATION memoryInfo;

    size_t nbBytes = ::VirtualQuery(memory, &memoryInfo, sizeof(MEMORY_BASIC_INFORMATION));

    if (nbBytes != 0)
    {
        return memoryInfo.RegionSize;
    }
    
    BW_LOG_ERROR(bw::LogChannel::eSYSTEM, "bw::memory::size(). %s", system::get_last_error_message());
    return 0;
}

}	// namespace bw