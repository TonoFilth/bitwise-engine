#include "Bw/Base/Memory/HeapAllocator.h"
#include "Bw/Base/Memory/PointerArithmetic.h"

namespace
{

using namespace bw;

////////////////////////////////////////////////////////////////////////////////
//  Private types
////////////////////////////////////////////////////////////////////////////////
struct Header
{
    size_t size;
    U8     _pad;
};

////////////////////////////////////////////////////////////////////////////////
//  Private functions
////////////////////////////////////////////////////////////////////////////////
BW_INLINE void add_header(void* addr, size_t totalSize)
{
    Header* header = (Header*) addr;
    header->size   = totalSize;
}

// -----------------------------------------------------------------------------

BW_INLINE void* data_pointer(void* addr, size_t alignment)
{
    U8 usedBytes;

    void* unalignedData = memory::pointer_add(addr, sizeof(Header));
    void* alignedData   = memory::align_forward(unalignedData, alignment, usedBytes);

    // If addr is already aligned adjustmentAddr
    // will overwrite Header::_pad member
    U8* adjustmentAddr = (U8*) alignedData - 1;
    *adjustmentAddr = usedBytes;

    return alignedData;
}

// -----------------------------------------------------------------------------

BW_INLINE Header* get_header(void* data)
{
    U8 adjustment  = *((U8*) data - 1);
    Header* header = (Header*) memory::pointer_sub(data, adjustment);

    return header - 1;
}

}   // private namespace

namespace bw
{

////////////////////////////////////////////////////////////////////////////////
//  Class std functions
////////////////////////////////////////////////////////////////////////////////
HeapAllocator::HeapAllocator(Allocator& backing, size_t heapSize) :
    m_addr(backing.allocate(heapSize)),
    m_backing(&backing),
    m_heapSize(heapSize),
    m_size(0)
{
}

// -----------------------------------------------------------------------------

HeapAllocator::HeapAllocator(Allocator* backing, void* heapAddr, size_t heapSize) :
    m_addr(heapAddr),
    m_backing(backing),
    m_heapSize(heapSize),
    m_size(0)
{
}

// -----------------------------------------------------------------------------

HeapAllocator::~HeapAllocator()
{
    BW_ASSERT(m_size == 0);

    if (m_backing)
    {
        m_backing->deallocate(m_addr);
    }
}

////////////////////////////////////////////////////////////////////////////////
//  Public functions
////////////////////////////////////////////////////////////////////////////////
void* HeapAllocator::allocate(size_t size, size_t alignment)
{
    size_t totalSize = sizeof(Header) + alignment - 1 + size;
    add_header(m_addr, totalSize);

    return data_pointer(m_addr, alignment);
}

// -----------------------------------------------------------------------------

void HeapAllocator::deallocate(void* data)
{
    Header* header = get_header(data);

    m_size -= header->size;
}

// -----------------------------------------------------------------------------

size_t HeapAllocator::allocatedSize() const
{
    return m_size;
}

// -----------------------------------------------------------------------------

size_t HeapAllocator::allocatedSize(void* data) const
{
    return get_header(data)->size;
}

}   // namespace bw