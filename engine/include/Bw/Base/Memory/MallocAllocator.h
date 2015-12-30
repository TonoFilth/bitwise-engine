#ifndef BW_BASE_MALLOC_ALLOCATOR_H
#define BW_BASE_MALLOC_ALLOCATOR_H

#include "Bw/Base/Memory/Allocator.h"

namespace bw
{

////////////////////////////////////////////////////////////////////////////////
//	MallocAllocator
////////////////////////////////////////////////////////////////////////////////
class BW_BASE_API MallocAllocator : public Allocator
{
public:
	MallocAllocator();
	virtual ~MallocAllocator() = default;

	void* allocate(size_t size, size_t alignment = kDefaultAlignment) override;
	void  deallocate(void* data) override;

	size_t allocatedSize()           const override;
	size_t allocatedSize(void* data) const override;
};

}	// namespace bw

#endif	// BW_BASE_MALLOC_ALLOCATOR_H