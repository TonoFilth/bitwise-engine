#ifndef BW_BASE_MEMORY_MODULE_INIT_H
#define BW_BASE_MEMORY_MODULE_INIT_H

#include "Bw/Base/Common/Module.h"
#include "Bw/Base/Memory/ModuleTypes.h"

namespace bw
{

////////////////////////////////////////////////////////////////////////////////
//  Initialization & shutdown
////////////////////////////////////////////////////////////////////////////////
BW_BASE_API void init_memory_system();
BW_BASE_API void init_memory_system(const MemoryConfig& config, uint32_t flags = MemoryConfig::eDEFAULT);
BW_BASE_API void shutdown_memory_system();

namespace memory
{

////////////////////////////////////////////////////////////////////////////////
//  Global allocators
////////////////////////////////////////////////////////////////////////////////
BW_BASE_API Allocator&   heap_allocator();
BW_BASE_API Allocator&   page_allocator();
BW_BASE_API MemoryConfig config();

}   // namespace memory
}   // namespace bw

#endif  // BW_BASE_MEMORY_MODULE_INIT_H