#include "bitwise/memory.h"
#include "bitwise/memory/internal.h"

namespace bw
{

// -----------------------------------------------------------------------------
//  Internal functions
// -----------------------------------------------------------------------------
void memory::initialize(int argc, char** argv)
{
    initialize_global_allocators();
}

// -----------------------------------------------------------------------------

void memory::shutdown()
{

}

}   // namespace bw