#ifndef BW_MEMORY_TYPES_H
#define BW_MEMORY_TYPES_H

namespace bw
{

////////////////////////////////////////////////////////////////////////////////
//  Allocator types
////////////////////////////////////////////////////////////////////////////////
class Allocator;
class PageAllocator;
class MallocAllocator;

template <class T>
class PoolAllocator;

template <unsigned T>
class ScopeAllocator;

}   // namespace bw

#endif  // BW_MEMORY_TYPES_H