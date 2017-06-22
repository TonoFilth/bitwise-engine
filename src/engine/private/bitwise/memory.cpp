#include "bitwise/memory.h"
#include "bitwise/memory/internal.h"

namespace bw
{
// -----------------------------------------------------------------------------
//  Internal functions
// -----------------------------------------------------------------------------
void internal::memory::initialize(int argc, char** argv)
{
    bw::internal::memory::create_global_allocators();
}

// -----------------------------------------------------------------------------

void internal::memory::shutdown()
{
    bw::internal::memory::delete_global_allocators();
}

}   // namespace bw