#include "bitwise/core/assert.h"
#include "bitwise/core/pointer.h"
#include "bitwise/core/system.h"
#include "bitwise/memory/page_allocator.h"
#include "bitwise/memory/internal.h"

// -----------------------------------------------------------------------------
//  Private methods
// -----------------------------------------------------------------------------
static size_t round_to_page_size(size_t sizeBytes)
{
    size_t pageSize = bw::system::page_size();

    if (sizeBytes % pageSize == 0)
    {
        return sizeBytes;
    }
    else
    {
        return ((sizeBytes / pageSize) + 1) * pageSize;
    }
}

namespace bw
{

////////////////////////////////////////////////////////////////////////////////
/// \details Detailed description.
/// \todo Write detailed description.
////////////////////////////////////////////////////////////////////////////////
PageAllocator::PageAllocator() :
    m_allocatedSize(0)
{
}

////////////////////////////////////////////////////////////////////////////////
/// \details Detailed description.
/// \todo Write detailed description.
////////////////////////////////////////////////////////////////////////////////
PageAllocator::~PageAllocator()
{
    BW_ASSERT(m_allocatedSize == 0, "Not all memory was freed.");
}

////////////////////////////////////////////////////////////////////////////////
/// \details Detailed description.
/// \todo Write detailed description.
////////////////////////////////////////////////////////////////////////////////
void* PageAllocator::allocate(size_t size, size_t* allocatedSize, size_t alignment)
{
    BW_ASSERT(size > 0, "Requested allocation size can't be 0");

    size = round_to_page_size(size);
    void* memory = bw::internal::memory::valloc(size);
    
    storeSize(memory, size);
    m_allocatedSize += size;

    if (allocatedSize != nullptr)
    {
        *allocatedSize = size;
    }

    return memory;
}

////////////////////////////////////////////////////////////////////////////////
/// \details Detailed description.
/// \todo Write detailed description.
////////////////////////////////////////////////////////////////////////////////
void PageAllocator::deallocate(void* memory)
{
    size_t size = regionSize(memory);
    
    bw::internal::memory::vfree(memory, size);
    deleteSize(memory);

    m_allocatedSize -= size;
}

////////////////////////////////////////////////////////////////////////////////
/// \details Detailed description.
/// \todo Write detailed description.
////////////////////////////////////////////////////////////////////////////////
size_t PageAllocator::allocatedSize() const
{
    return m_allocatedSize;
}

////////////////////////////////////////////////////////////////////////////////
/// \details Detailed description.
/// \todo Write detailed description.
////////////////////////////////////////////////////////////////////////////////
size_t PageAllocator::allocatedSize(void* memory) const
{
    return regionSize(memory);
}

}	// namespace bw