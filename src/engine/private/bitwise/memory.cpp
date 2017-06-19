#include "bitwise/memory.h"
#include "bitwise/memory/internal.h"

namespace bw
{

// -----------------------------------------------------------------------------
//  Internal functions
// -----------------------------------------------------------------------------
void memory::initialize(int argc, char** argv)
{
    create_global_allocators();
}

// -----------------------------------------------------------------------------

void memory::shutdown()
{
    delete_global_allocators();
}

}   // namespace bw