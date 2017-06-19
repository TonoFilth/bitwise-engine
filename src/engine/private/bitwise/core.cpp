#include "bitwise/core.h"
#include "bitwise/core/internal.h"

namespace bw
{

// -----------------------------------------------------------------------------
//  Internal functions
// -----------------------------------------------------------------------------
void core::initialize(int argc, char** argv)
{
    system::initialize(argc, argv);
}

// -----------------------------------------------------------------------------

void core::shutdown()
{
    system::shutdown();
}

}   // namespace bw