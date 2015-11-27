#ifndef BW_BASE_HEAP_ALLOCATOR_H
#define BW_BASE_HEAP_ALLOCATOR_H

#include "Bw/Base/Common/Module.h"
#include "Bw/Base/Memory/Allocator.h"

namespace bw
{

////////////////////////////////////////////////////////////////////////////////
//  HeapAllocator
////////////////////////////////////////////////////////////////////////////////
class BW_BASE_API HeapAllocator : public Allocator
{
public:
    HeapAllocator();
    HeapAllocator(void* heapAddr, size_t heapSize);
    virtual ~HeapAllocator();

    void* allocate(size_t size, size_t alignment) override;
    void  deallocate(void* data) override;

    size_t allocatedSize()           const override;
    size_t allocatedSize(void* data) const override;
};

}   // namespace bw

#endif  // BW_BASE_HEAP_ALLOCATOR_H