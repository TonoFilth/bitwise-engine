#include "Bw/Base/Memory/MallocAllocator.h"

namespace bw
{

////////////////////////////////////////////////////////////////////////////////
//  Class std functions
////////////////////////////////////////////////////////////////////////////////
MallocAllocator::MallocAllocator()
{
}

////////////////////////////////////////////////////////////////////////////////
//  Public functions
////////////////////////////////////////////////////////////////////////////////
void* MallocAllocator::allocate(size_t size, size_t alignment)
{
	return _aligned_malloc(size, alignment);
}

// -----------------------------------------------------------------------------

void MallocAllocator::deallocate(void* data)
{
	return _aligned_free(data);
}

// -----------------------------------------------------------------------------

size_t MallocAllocator::allocatedSize() const
{
	return Allocator::kSizeNotTracked;
}

// -----------------------------------------------------------------------------

size_t MallocAllocator::allocatedSize(void* data) const
{
	return Allocator::kSizeNotTracked;
}

}	// namespace bw