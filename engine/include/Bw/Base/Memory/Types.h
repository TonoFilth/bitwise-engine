#ifndef BW_BASE_MEMORY_TYPES_H
#define BW_BASE_MEMORY_TYPES_H

#include "Bw/Base/Common/Types.h"

namespace bw
{

////////////////////////////////////////////////////////////////////////////////
//  Allocator types
////////////////////////////////////////////////////////////////////////////////
class Allocator;
class PageAllocator;
class HeapAllocator;

template <class T>
class PoolAllocator;

template <unsigned T>
class ScopeAllocator;

}   // namespace bw

#endif  // BW_BASE_MEMORY_TYPES_H