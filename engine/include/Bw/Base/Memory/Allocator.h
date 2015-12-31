#ifndef BW_BASE_ALLOCATOR_H
#define BW_BASE_ALLOCATOR_H

#include <new>      // placement new
#include <utility>  // std::forward
#include "Bw/Base/Config.h"
#include "Bw/Base/Common/Limits.h"

namespace bw
{

////////////////////////////////////////////////////////////////////////////////
//  Allocator
////////////////////////////////////////////////////////////////////////////////
class BW_BASE_API Allocator
{
public:
	static const size_t kSizeNotTracked   = BW_SIZE_MAX;
    static const size_t kDefaultAlignment = 4;

public:
    Allocator()          = default;
    virtual ~Allocator() = default;

    Allocator(const Allocator& toCopy)             = delete;
    Allocator& operator=(const Allocator& toCopy)  = delete;

public:
    virtual void* allocate(size_t size, size_t alignment = kDefaultAlignment) = 0;
    virtual void  deallocate(void* data) = 0;

    virtual size_t allocatedSize()           const = 0;
    virtual size_t allocatedSize(void* data) const = 0;

public:
    template <class T, class ...Args>
    T* allocateObject(Args&& ...args);

    template <class T>
    void deallocateObject(T* ptr);
};

#include "Bw/Base/Detail/Allocator.inl"

}   // namespace bw

#endif  // BW_BASE_ALLOCATOR_H