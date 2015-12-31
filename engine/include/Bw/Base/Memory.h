#ifndef BW_BASE_MEMORY_MODULE_H
#define BW_BASE_MEMORY_MODULE_H

#include "Bw/Base/Memory/Allocator.h"
#include "Bw/Base/Memory/Common.h"
#include "Bw/Base/Memory/HeapAllocator.h"
#include "Bw/Base/Memory/MallocAllocator.h"
#include "Bw/Base/Memory/PageAllocator.h"
#include "Bw/Base/Memory/PoolAllocator.h"
#include "Bw/Base/Memory/ScopeAllocator.h"
#include "Bw/Base/Memory/Types.h"
#include "Bw/Base/Memory/Utils.h"

namespace bw
{
namespace Internal
{

////////////////////////////////////////////////////////////////////////////////
//  Initialization & shutdown
////////////////////////////////////////////////////////////////////////////////
BW_BASE_API void InitMemory();
BW_BASE_API void QuitMemory();

}	// namespace Internal
}	// namespace bw

#endif  // BW_BASE_MEMORY_MODULE_H