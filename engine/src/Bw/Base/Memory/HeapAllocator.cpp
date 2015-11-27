#include "Bw/Base/Memory/HeapAllocator.h"

namespace bw
{

////////////////////////////////////////////////////////////////////////////////
//  Class std functions
////////////////////////////////////////////////////////////////////////////////
HeapAllocator::HeapAllocator()
{
}

// -----------------------------------------------------------------------------

HeapAllocator::HeapAllocator(void* heapAddr, size_t heapSize)
{

}

// -----------------------------------------------------------------------------

HeapAllocator::~HeapAllocator()
{

}

////////////////////////////////////////////////////////////////////////////////
//  Public functions
////////////////////////////////////////////////////////////////////////////////
void* HeapAllocator::allocate(size_t size, size_t alignment)
{
    return nullptr;
}

// -----------------------------------------------------------------------------

void HeapAllocator::deallocate(void* data)
{

}

// -----------------------------------------------------------------------------

size_t HeapAllocator::allocatedSize() const
{
    return Allocator::kSizeNotTracked;
}

// -----------------------------------------------------------------------------

size_t HeapAllocator::allocatedSize(void* data) const
{
    return Allocator::kSizeNotTracked;
}

}   // namespace bw