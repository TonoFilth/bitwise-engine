#include <new>  // placement new

#include "bitwise/memory/global_allocators.h"
#include "bitwise/memory/allocator.h"
#include "bitwise/memory/page_allocator.h"
#include "bitwise/memory/heap_allocator.h"
#include "bitwise/memory/internal.h"

// -----------------------------------------------------------------------------
//  Constants
// -----------------------------------------------------------------------------
static const size_t kMaxGlobalAllocatorBuffer = 16;

// -----------------------------------------------------------------------------
//  Private variables
// -----------------------------------------------------------------------------
static char m_allocatorBuffer[kMaxGlobalAllocatorBuffer];

// -----------------------------------------------------------------------------

static bw::Allocator* m_pageAllocator    = nullptr;
static bw::Allocator* m_heapAllocator    = nullptr;
static bw::Allocator* m_genericAllocator = nullptr;

// -----------------------------------------------------------------------------
//  Private functions
// -----------------------------------------------------------------------------
void bw::memory::initialize_global_allocators()
{
    static_assert(sizeof(PageAllocator) + sizeof(HeapAllocator) < kMaxGlobalAllocatorBuffer, "Buffer too small");

    char* memory = m_allocatorBuffer;

    m_pageAllocator = (bw::Allocator*) new (memory) PageAllocator();
    memory += sizeof(PageAllocator);
    m_heapAllocator = (bw::Allocator*) new (memory) HeapAllocator();

    m_genericAllocator = m_heapAllocator;
}

namespace bw
{

////////////////////////////////////////////////////////////////////////////////
/// \details Detailed description.
/// \todo Write detailed description.
////////////////////////////////////////////////////////////////////////////////
Allocator& memory::generic_allocator()
{
    return *m_genericAllocator;
}

////////////////////////////////////////////////////////////////////////////////
/// \details Detailed description.
/// \todo Write detailed description.
////////////////////////////////////////////////////////////////////////////////
Allocator& memory::page_allocator()
{
    return *m_pageAllocator;
}

////////////////////////////////////////////////////////////////////////////////
/// \details Detailed description.
/// \todo Write detailed description.
////////////////////////////////////////////////////////////////////////////////
Allocator& memory::heap_allocator()
{
    return *m_heapAllocator;
}

}	// namespace bw