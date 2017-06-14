#include "bitwise.h"
#include "bitwise/core/internal.h"
#include "bitwise/math/internal.h"

////////////////////////////////////////////////////////////////////////////////
/// \details Detailed description.
/// \todo Write detailed description.
////////////////////////////////////////////////////////////////////////////////
void bw::initialize(int argc, char** argv)
{
    BW_CALL_ONCE();

    core::initialize(argc, argv);
    math::initialize(argc, argv);
}

////////////////////////////////////////////////////////////////////////////////
/// \details Detailed description.
/// \todo Write detailed description.
////////////////////////////////////////////////////////////////////////////////
void bw::shutdown()
{
    BW_CALL_ONCE();

    math::shutdown();
    core::shutdown();
}