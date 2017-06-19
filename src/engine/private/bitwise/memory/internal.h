#if !defined(BW_DOXYPRESS)
#pragma once

namespace bw
{
namespace memory
{
    // -------------------------------------------------------------------------
    //  Internal functions
    // -------------------------------------------------------------------------
    void initialize(int argc, char** argv);
    void shutdown();
    void create_global_allocators();
    void delete_global_allocators();
    void* alloc(size_t sizeBytes);
    void free(void* data, size_t sizeBytes);

}   // namespace memory
}   // namespace bw

#endif