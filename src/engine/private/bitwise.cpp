#include "bitwise.h"
#include "bitwise/collections/internal.h"
#include "bitwise/concurrency/internal.h"
#include "bitwise/core/internal.h"
#include "bitwise/log/internal.h"
#include "bitwise/math/internal.h"
#include "bitwise/memory/internal.h"
#include "bitwise/network/internal.h"

////////////////////////////////////////////////////////////////////////////////
/// \details Detailed description.
/// \todo Write detailed description.
////////////////////////////////////////////////////////////////////////////////
void bw::initialize(int argc, char** argv)
{
    BW_CALL_ONCE();

    bw::internal::log::initialize(argc, argv);

    BW_LOG_INFO(LogChannel::eSYSTEM, "Initializing bitwise engine");

    bw::internal::core::initialize(argc, argv);
    bw::internal::memory::initialize(argc, argv);
	bw::internal::concurrency::initialize(argc, argv);
    bw::internal::collections::initialize(argc, argv);
	bw::internal::network::initialize(argc, argv);
    bw::internal::math::initialize(argc, argv);

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

    bw::internal::math::shutdown();
	bw::internal::network::shutdown();
    bw::internal::collections::shutdown();
	bw::internal::concurrency::shutdown();
    bw::internal::memory::shutdown();
    bw::internal::core::shutdown();
    bw::internal::log::shutdown();

    BW_LOG_INFO(LogChannel::eSYSTEM, "Bitwise engine shutted down");
}