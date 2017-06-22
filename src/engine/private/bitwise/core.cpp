#include "bitwise/core.h"
#include "bitwise/core/internal.h"

namespace bw
{

// -----------------------------------------------------------------------------
//  Internal functions
// -----------------------------------------------------------------------------
void internal::core::initialize(int argc, char** argv)
{
    bw::internal::system::initialize(argc, argv);
}

// -----------------------------------------------------------------------------

void internal::core::shutdown()
{
    bw::internal::system::shutdown();
}

}   // namespace bw