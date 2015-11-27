#ifndef BW_BASE_ALLOCATOR_H
#define BW_BASE_ALLOCATOR_H

#include <new>      // Placement new
#include <limits>   // std::numeric_limits
#include <utility>  // std::forward
#include "Bw/Base/Common/Module.h"

namespace bw
{

////////////////////////////////////////////////////////////////////////////////
//  Allocator
////////////////////////////////////////////////////////////////////////////////
class BW_BASE_API Allocator
{
public:
    const size_t kSizeNotTracked = std::numeric_limits<size_t>::max();

    Allocator() = default;
    virtual ~Allocator() = default;

    virtual void* allocate(size_t size, size_t alignment) = 0;
    virtual void  deallocate(void* data) = 0;

    virtual size_t allocatedSize()           const = 0;
    virtual size_t allocatedSize(void* data) const = 0;

public:
    template <class T, class ...Args>
    T* makeNew(Args&& ...args);

    template <class T>
    void makeDelete(T* ptr);

private:
    // Allocators cannot be copied
    Allocator(const Allocator& toCopy);
    Allocator& operator=(const Allocator& toCopy);
};

#include "Bw/Base/_detail/Allocator.inl"

}   // namespace bw

#endif  // BW_BASE_ALLOCATOR_H