#ifndef BW_BASE_TCMALLOC_ALLOCATOR_H
#define BW_BASE_TCMALLOC_ALLOCATOR_H

#include "Bw/Base/Memory/Allocator.h"

namespace bw
{

////////////////////////////////////////////////////////////////////////////////
//  TCMallocAllocator
////////////////////////////////////////////////////////////////////////////////
class BW_BASE_API TCMallocAllocator : public Allocator
{
public:
	TCMallocAllocator();
	virtual ~TCMallocAllocator();

	void* allocate(size_t size, size_t alignment) override;
	void  deallocate(void* data) override;

	size_t allocatedSize() const override;
	size_t allocatedSize(void* data) const override;

private:
	void* allocateSmallObject(size_t size, size_t alignment);
	void* allocateLargeObject(size_t size, size_t alignment);
};

}	// namespace bw

#endif	// BW_BASE_TCMALLOC_ALLOCATOR_H