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
    void initialize_global_allocators();
    void shutdown();

}   // namespace memory
}   // namespace bw

#endif