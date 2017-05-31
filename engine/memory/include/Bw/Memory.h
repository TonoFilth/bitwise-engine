#ifndef BW_MEMORY_MODULE_H
#define BW_MEMORY_MODULE_H

#include "Bw/Memory/Allocator.h"
#include "Bw/Memory/Common.h"
#include "Bw/Memory/Export.h"
#include "Bw/Memory/MallocAllocator.h"
#include "Bw/Memory/PageAllocator.h"
#include "Bw/Memory/PoolAllocator.h"
#include "Bw/Memory/ScopeAllocator.h"
#include "Bw/Memory/Types.h"
#include "Bw/Memory/Utils.h"

namespace bw
{
namespace Internal
{

////////////////////////////////////////////////////////////////////////////////
//	Public functions
////////////////////////////////////////////////////////////////////////////////
BW_MEMORY_API void InitializeMemoryModule();
BW_MEMORY_API void ShutdownMemoryModule();

}	// namespace Internal
}	// namespace bw

#endif	// BW_MEMORY_MODULE_H