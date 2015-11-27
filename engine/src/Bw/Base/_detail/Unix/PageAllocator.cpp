#include <sys/mman.h>
#include "Bw/Base/Memory/PageAllocator.h"
#include "Bw/Base/System.h"

namespace
{

using namespace bw;

////////////////////////////////////////////////////////////////////////////////
//  Private variables
////////////////////////////////////////////////////////////////////////////////
size_t s_PageSize = 0;

////////////////////////////////////////////////////////////////////////////////
//  Private functions
////////////////////////////////////////////////////////////////////////////////
BW_INLINE size_t size_to_pages(size_t size)
{
    return size / s_PageSize;
}

////////////////////////////////////////////////////////////////////////////////
//  Private types
////////////////////////////////////////////////////////////////////////////////
struct Header
{
    U16 pageCount;
};

}   // private namespace

namespace bw
{

////////////////////////////////////////////////////////////////////////////////
//  Class std functions
////////////////////////////////////////////////////////////////////////////////
PageAllocator::PageAllocator() :
    m_totalAllocated(0)
{
    // The first instance of the PageAllocator class must save the
    // system page size
    if (s_PageSize == 0)
    {
        s_PageSize = system::get_page_size();

        // Make sure the page size is valid
        BW_ASSERT(s_PageSize > 0);
    }
}

// -----------------------------------------------------------------------------

PageAllocator::~PageAllocator()
{
    BW_ASSERT(m_totalAllocated == 0);
}

////////////////////////////////////////////////////////////////////////////////
//  Public functions
////////////////////////////////////////////////////////////////////////////////
void* PageAllocator::allocate(size_t size, size_t alignment)
{
    // Translate the size of this allocation to system pages
    //size_t nbPages = size_to_pages(size);

    void* rawAddr = ::mmap(0, size, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);

    m_totalAllocated += size;

    return rawAddr;
}

// -----------------------------------------------------------------------------

void PageAllocator::deallocate(void* data)
{
    int status = ::munmap(data, s_PageSize);

    // Check for errors
    if (status != 0)
    {

    }
    else
    {
        m_totalAllocated -= s_PageSize;
    }
}

// -----------------------------------------------------------------------------

size_t PageAllocator::allocatedSize() const
{
    return m_totalAllocated;
}

// -----------------------------------------------------------------------------

size_t PageAllocator::allocatedSize(void* data) const
{
    return 0;
}

}   // namespace bw