#if !defined(BW_DOXYPRESS)
#pragma once

namespace bw
{
// -----------------------------------------------------------------------------
//  Internal namespace
// -----------------------------------------------------------------------------
namespace internal
{
namespace memory
{
    // Defined in "bitwise/memory.cpp"
    void initialize(int argc, char** argv);
    void shutdown();

    // Defined in "bitwise/memory/global_allocators.cpp"
    void create_global_allocators();
    void delete_global_allocators();

    // Defined in "bitwise/memory/platform/<platform>_alloc.cpp"
    void* valloc(size_t sizeBytes);
    void  vfree(void* memory, size_t sizeBytes);
    void* malloc(size_t sizeBytes, size_t alignment);   // Temporal function until custom implementation of HeapAllocator
    void  mfree(void* memory);                          // Temporal function until custom implementation of HeapAllocator
}
}   // namespace internal
}   // namespace bw

#endif