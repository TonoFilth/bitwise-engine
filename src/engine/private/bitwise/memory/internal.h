#if !defined(BW_DOXYPRESS)
#pragma once

namespace bw
{

// -----------------------------------------------------------------------------
//  Forward declarations
// -----------------------------------------------------------------------------
class PageAllocator;

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
    void free(void* memory, size_t sizeBytes);

    void   save_size  (PageAllocator& allocator, void* memory, size_t size);
    void   delete_size(PageAllocator& allocator, void* memory);
    size_t size       (const PageAllocator& allocator, void* memory);

}   // namespace memory
}   // namespace bw

#endif