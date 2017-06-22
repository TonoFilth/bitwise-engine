#include "bitwise/core/assert.h"
#include "bitwise/core/pointer.h"
#include "bitwise/core/system.h"
#include "bitwise/core/cstring.h"
#include "bitwise/memory/page_allocator.h"
#include "bitwise/memory/internal.h"

// -----------------------------------------------------------------------------
//  Private variables
// -----------------------------------------------------------------------------
static size_t m_pageSize = 0;

// -----------------------------------------------------------------------------
//  Private methods
// -----------------------------------------------------------------------------
static size_t round_to_page_size(size_t sizeBytes)
{
    if (sizeBytes % m_pageSize == 0)
    {
        return sizeBytes;
    }
    else
    {
        return ((sizeBytes / m_pageSize) + 1) * m_pageSize;
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

    if (m_pageSize == 0)
    {
        m_pageSize = system::page_size();
    }

    size = round_to_page_size(size);
    void* memory = memory::alloc(size);
    
    memory::save_size(*this, memory, size);
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
    size_t size = memory::size(*this, memory);
    
    memory::free(memory, size);
    memory::delete_size(*this, memory);

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
    return memory::size(*this, memory);
}

}	// namespace bw