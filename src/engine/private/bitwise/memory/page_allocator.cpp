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
//  Private types
// -----------------------------------------------------------------------------
struct Allocation
{
    void* memory;
    size_t size;
};

// -----------------------------------------------------------------------------

struct AllocationList
{
    size_t allocatedSize;
    void*  maxAddress;
    void*  freeMemory;
};

// -----------------------------------------------------------------------------
//  Private methods
// -----------------------------------------------------------------------------
static void* grow(void* listMemory)
{
    AllocationList* list = (AllocationList*) listMemory;

    ptrdiff_t diff = uintptr_t(list->maxAddress) - uintptr_t(list);
    size_t newListSize = diff * 2;
    AllocationList* newList = (AllocationList*) bw::memory::alloc(newListSize);

    newList->allocatedSize = list->allocatedSize;
    newList->freeMemory    = bw::pointer::add(newList, uintptr_t(list->freeMemory) - uintptr_t(list));
    newList->maxAddress    = bw::pointer::add(newList, newListSize);

    void* prevStartAddress = bw::pointer::align_forward(bw::pointer::add(list,    sizeof(AllocationList)), alignof(Allocation));
    void* newStartAddress  = bw::pointer::align_forward(bw::pointer::add(newList, sizeof(AllocationList)), alignof(Allocation));

    memcpy_s(newStartAddress, newListSize - sizeof(AllocationList), prevStartAddress, diff - sizeof(AllocationList));

    bw::memory::free(list, diff);

    return newList;
}

// -----------------------------------------------------------------------------

static AllocationList* create_allocation_list()
{
    AllocationList* list = (AllocationList*) bw::memory::alloc(m_pageSize);

    list->allocatedSize = 0;
    list->maxAddress    = bw::pointer::add(list, m_pageSize);
    list->freeMemory    = bw::pointer::align_forward(bw::pointer::add(list, sizeof(AllocationList)), alignof(Allocation));

    return list;
}

// -----------------------------------------------------------------------------

static Allocation* create_allocation_node(void*& listMemory, size_t sizeBytes)
{
    AllocationList* list = (AllocationList*) listMemory;

    if (bw::pointer::add(list->freeMemory, sizeof(Allocation)) >= list->maxAddress)
    {
        listMemory = grow(listMemory);
        list = (AllocationList*) listMemory;
    }

    Allocation* allocation = (Allocation*) list->freeMemory;

    list->allocatedSize += sizeBytes;
    list->freeMemory     = (Allocation*) list->freeMemory + 1;

    allocation->size   = sizeBytes;
    allocation->memory = bw::memory::alloc(sizeBytes);
    
    return allocation;
}

// -----------------------------------------------------------------------------

static Allocation* find_allocation(void* listMemory, void* memory)
{
    AllocationList* list = (AllocationList*) listMemory;
    Allocation* allocation = (Allocation*) bw::pointer::align_forward(bw::pointer::add(list, sizeof(AllocationList)), alignof(Allocation));

    while (allocation < list->freeMemory)
    {
        if (allocation->memory == memory)
        {
            return allocation;
        }

        ++allocation;
    }

    return nullptr;
}

// -----------------------------------------------------------------------------

static void free_memory(void* listMemory, void* memory)
{
    AllocationList* list = (AllocationList*) listMemory;
    Allocation* allocation = find_allocation(listMemory, memory);

    BW_ASSERT(allocation != nullptr, "Can't find allocation node {0}", memory);

    bw::memory::free(allocation->memory, allocation->size);
    list->allocatedSize -= allocation->size;
    
    Allocation* next = allocation + 1;

    while (next < list->freeMemory)
    {
        allocation->size   = next->size;
        allocation->memory = next->memory;

        allocation = next;
        ++next;
    }

    allocation->size   = 0;
    allocation->memory = nullptr;

    list->freeMemory = allocation;
}

namespace bw
{

////////////////////////////////////////////////////////////////////////////////
/// \details Detailed description.
/// \todo Write detailed description.
////////////////////////////////////////////////////////////////////////////////
PageAllocator::PageAllocator() :
    m_data(nullptr)
{
}

////////////////////////////////////////////////////////////////////////////////
/// \details Detailed description.
/// \todo Write detailed description.
////////////////////////////////////////////////////////////////////////////////
PageAllocator::~PageAllocator()
{
    if (m_data != nullptr)
    {
        AllocationList* list = (AllocationList*) m_data;

        BW_ASSERT(list->allocatedSize == 0, "Not all memory was freed.");

        ptrdiff_t size = uintptr_t(list->maxAddress) - uintptr_t(list);
        memory::free(m_data, size);
        m_data = nullptr;
    }
}

////////////////////////////////////////////////////////////////////////////////
/// \details Detailed description.
/// \todo Write detailed description.
////////////////////////////////////////////////////////////////////////////////
void* PageAllocator::allocate(size_t size, size_t alignment)
{
    if (m_data == nullptr)
    {
        m_pageSize = system::page_size();
        m_data     = create_allocation_list();
    }

    return create_allocation_node(m_data, size)->memory;
}

////////////////////////////////////////////////////////////////////////////////
/// \details Detailed description.
/// \todo Write detailed description.
////////////////////////////////////////////////////////////////////////////////
void PageAllocator::deallocate(void* memory)
{
    free_memory(m_data, memory);
}

////////////////////////////////////////////////////////////////////////////////
/// \details Detailed description.
/// \todo Write detailed description.
////////////////////////////////////////////////////////////////////////////////
size_t PageAllocator::allocatedSize() const
{
    return (m_data != nullptr ? ((AllocationList*) m_data)->allocatedSize : 0);
}

////////////////////////////////////////////////////////////////////////////////
/// \details Detailed description.
/// \todo Write detailed description.
////////////////////////////////////////////////////////////////////////////////
size_t PageAllocator::allocatedSize(void* memory) const
{
    return find_allocation(m_data, memory)->size;
}

}	// namespace bw