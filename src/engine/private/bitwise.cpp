#include "bitwise.h"
#include "bitwise/core/internal.h"
#include "bitwise/math/internal.h"
#include "bitwise/log/internal.h"
#include "bitwise/memory/internal.h"

////////////////////////////////////////////////////////////////////////////////
/// \details Detailed description.
/// \todo Write detailed description.
////////////////////////////////////////////////////////////////////////////////
void bw::initialize(int argc, char** argv)
{
    BW_CALL_ONCE();

    log::initialize(argc, argv);

    BW_LOG_INFO(LogChannel::eSYSTEM, "Initializing bitwise engine");

    core::initialize(argc, argv);
    memory::initialize(argc, argv);
    math::initialize(argc, argv);

    BW_LOG_INFO(LogChannel::eSYSTEM, "Bitwise engine initialized");
}

////////////////////////////////////////////////////////////////////////////////
/// \details Detailed description.
/// \todo Write detailed description.
////////////////////////////////////////////////////////////////////////////////
void bw::shutdown()
{
    BW_CALL_ONCE();

    BW_LOG_INFO(LogChannel::eSYSTEM, "Shutting down bitwise engine");

    math::shutdown();
    memory::shutdown();
    core::shutdown();
    log::shutdown();

    BW_LOG_INFO(LogChannel::eSYSTEM, "Bitwise engine shutted down");
}