#include "bitwise/memory/page_allocator.h"
#include "bitwise/core/internal.h"
#include "bitwise/log.h"

#include <Windows.h>

namespace bw
{

////////////////////////////////////////////////////////////////////////////////
/// \details Detailed description.
/// \todo Write detailed description.
////////////////////////////////////////////////////////////////////////////////
void PageAllocator::storeSize(void* memory, size_t sizeBytes)
{
}

////////////////////////////////////////////////////////////////////////////////
/// \details Detailed description.
/// \todo Write detailed description.
////////////////////////////////////////////////////////////////////////////////
void PageAllocator::deleteSize(void* memory)
{
}

////////////////////////////////////////////////////////////////////////////////
/// \details Detailed description.
/// \todo Write detailed description.
////////////////////////////////////////////////////////////////////////////////
size_t PageAllocator::regionSize(void* memory) const
{
    MEMORY_BASIC_INFORMATION memoryInfo;

    size_t nbBytes = ::VirtualQuery(memory, &memoryInfo, sizeof(MEMORY_BASIC_INFORMATION));

    if (nbBytes != 0)
    {
        return memoryInfo.RegionSize;
    }
    
    BW_LOG_ERROR(bw::LogChannel::eSYSTEM, "bw::memory::size(). %s", bw::internal::system::get_last_error_message());
    return 0;
}

}	// namespace bw