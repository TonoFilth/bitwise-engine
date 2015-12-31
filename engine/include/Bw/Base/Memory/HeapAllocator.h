#ifndef BW_BASE_HEAP_ALLOCATOR_H
#define BW_BASE_HEAP_ALLOCATOR_H

#include "Bw/Base/Memory/Allocator.h"

namespace bw
{

////////////////////////////////////////////////////////////////////////////////
//  HeapAllocator
////////////////////////////////////////////////////////////////////////////////
class BW_BASE_API HeapAllocator : public Allocator
{
public:
    HeapAllocator(Allocator& backing, size_t heapSize);
    HeapAllocator(Allocator* backing, void* heapAddr, size_t heapSize);
    virtual ~HeapAllocator();

    void* allocate(size_t size, size_t alignment) override;
    void  deallocate(void* data) override;

    size_t allocatedSize()           const override;
    size_t allocatedSize(void* data) const override;

private:
    void*      m_addr;
    Allocator* m_backing;
    size_t     m_heapSize;
    size_t     m_size;
};

}   // namespace bw

#endif  // BW_BASE_HEAP_ALLOCATOR_H