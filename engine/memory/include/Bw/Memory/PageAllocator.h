#ifndef BW_MEMORY_PAGE_ALLOCATOR_H
#define BW_MEMORY_PAGE_ALLOCATOR_H

#include "Bw/Memory/Allocator.h"

namespace bw
{

////////////////////////////////////////////////////////////////////////////////
//  PageAllocator
////////////////////////////////////////////////////////////////////////////////
class BW_MEMORY_API PageAllocator : public Allocator
{
public:
    PageAllocator();
    virtual ~PageAllocator();

    void* allocate(size_t size, size_t alignment) override;
    void  deallocate(void* data) override;

    size_t allocatedSize()           const override;
    size_t allocatedSize(void* data) const override;

private:
	void*  m_list;
    size_t m_totalAllocated;
};

}   // namespace bw

#endif  // BW_MEMORY_PAGE_ALLOCATOR_H