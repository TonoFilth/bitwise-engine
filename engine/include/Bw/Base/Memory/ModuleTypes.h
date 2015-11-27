#ifndef BW_BASE_MEMORY_TYPES_MODULE_H
#define BW_BASE_MEMORY_TYPES_MODULE_H

#include "Bw/Base/Common/Module.h"

namespace bw
{

////////////////////////////////////////////////////////////////////////////////
//  Allocator types
////////////////////////////////////////////////////////////////////////////////
class Allocator;
class PageAllocator;
class HeapAllocator;

////////////////////////////////////////////////////////////////////////////////
//  Memory system configuration
////////////////////////////////////////////////////////////////////////////////
struct BW_BASE_API MemoryConfig
{
    size_t retail;      // Main memory hard limit
    size_t debug;       // Debug memory hard limit
    size_t globalHeap;  // Global heap hard limit

    enum Enum
    {
        eDEFAULT     = 0,
        eSTRICT      = 1 << 1,  // Don't treat sizes as hints
        eMERGE_DEBUG = 1 << 2   // Merge debug memory in retail memory
    };
};

}   // namespace bw

#endif  // BW_BASE_MEMORY_TYPES_MODULE_H