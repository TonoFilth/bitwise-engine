#include "Bw/Memory/MallocAllocator.h"

#if !defined(BW_SYSTEM_WINDOWS)
#	include <cstdlib>
#endif

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
#if defined(BW_SYSTEM_WINDOWS)
	return _aligned_malloc(size, alignment);
#else
	void* memory = nullptr;
	::posix_memalign(&memory, alignment, size);

	return memory;
#endif
}

// -----------------------------------------------------------------------------

void MallocAllocator::deallocate(void* data)
{
	if (data == nullptr)
	{
		return;
	}

#if defined(BW_SYSTEM_WINDOWS)
	_aligned_free(data);
#else
	::free(data);
#endif
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