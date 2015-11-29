#include <new>
#include "Bw/Base/Memory/ModuleInit.h"
#include "Bw/Base/Memory/HeapAllocator.h"
#include "Bw/Base/Memory/PageAllocator.h"
#include "Bw/Base/System.h"

namespace
{

using namespace bw;

////////////////////////////////////////////////////////////////////////////////
//  Private constants
////////////////////////////////////////////////////////////////////////////////
const size_t BUFFER_SIZE = 1024;    // Bytes

////////////////////////////////////////////////////////////////////////////////
//  Private variables
////////////////////////////////////////////////////////////////////////////////
char _Buffer[BUFFER_SIZE];
MemoryConfig _MemConfig { 0, 0, 0 };

HeapAllocator* _StaticHeap    = nullptr;
HeapAllocator* _GlobalHeap    = nullptr;
PageAllocator* _PageAllocator = nullptr;

////////////////////////////////////////////////////////////////////////////////
//  Private functions
////////////////////////////////////////////////////////////////////////////////
#ifdef BW_DEBUG
void check_memory_config(const MemoryConfig& config)
{
    BW_ASSERT(config.globalHeap < config.retail);
}
#endif

// -----------------------------------------------------------------------------

void init_allocators(const MemoryConfig& config, u32_t flags)
{
    // Make sure the memory system wasn't initialized
    BW_ASSERT(_StaticHeap == nullptr);

#ifdef BW_DEBUG
    check_memory_config(config);
#endif

    _StaticHeap = new (_Buffer) HeapAllocator(nullptr, _Buffer + sizeof(HeapAllocator),
        BUFFER_SIZE - sizeof(HeapAllocator));

    _PageAllocator = _StaticHeap->allocateObject<PageAllocator>();
    //_GlobalHeap    = _StaticHeap->allocateObject<HeapAllocator>(*_PageAllocator, config.globalHeap);

    // Store memory configuration
    _MemConfig = config;
}

}   // private namespace

namespace bw
{

////////////////////////////////////////////////////////////////////////////////
//  Public functions
////////////////////////////////////////////////////////////////////////////////
BW_BASE_API void init_memory_system()
{
    MemoryConfig config;

    config.retail     = 1024 * 1000 * 128;
    config.debug      = 1024 * 1000 * 64;
    config.globalHeap = 1024 * 1000 * 64;

    init_allocators(config, MemoryConfig::eDEFAULT);
}

// -----------------------------------------------------------------------------

BW_BASE_API void init_memory_system(const MemoryConfig& config, u32_t flags)
{
    init_allocators(config, flags);
}

// -----------------------------------------------------------------------------

BW_BASE_API void shutdown_memory_system()
{
    // Make sure the memory system was initialized
    BW_ASSERT(_StaticHeap != nullptr);

    _StaticHeap->deallocateObject<HeapAllocator>(_GlobalHeap);
    _GlobalHeap = nullptr;

    _StaticHeap->deallocateObject<PageAllocator>(_PageAllocator);
    _PageAllocator = nullptr;

    _StaticHeap->~HeapAllocator();
    _StaticHeap = nullptr;

    // Restore default memory configuration
    _MemConfig.retail     = 0;
    _MemConfig.debug      = 0;
    _MemConfig.globalHeap = 0;
}

// -----------------------------------------------------------------------------

BW_BASE_API Allocator& memory::heap_allocator()
{
    return *_GlobalHeap;
}

// -----------------------------------------------------------------------------

BW_BASE_API Allocator& memory::page_allocator()
{
    return *_PageAllocator;
}

// -----------------------------------------------------------------------------

BW_BASE_API MemoryConfig memory::config()
{
    return _MemConfig;
}

}   // namespace bw