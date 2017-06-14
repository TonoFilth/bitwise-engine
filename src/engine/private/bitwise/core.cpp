#include "bitwise/core.h"
#include "bitwise/core/internal.h"

namespace bw
{

// -----------------------------------------------------------------------------
//  Internal functions
// -----------------------------------------------------------------------------
void core::initialize(int argc, char** argv)
{
    log::initialize();
}

// -----------------------------------------------------------------------------

void core::shutdown()
{
    log::shutdown();
}

}   // namespace bw