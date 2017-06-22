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

    // Defined in "bitwise/memory/platform/<platform>_valloc.cpp"
    void* valloc(size_t sizeBytes);
    void  vfree(void* memory, size_t sizeBytes);
}
}   // namespace internal
}   // namespace bw

#endif