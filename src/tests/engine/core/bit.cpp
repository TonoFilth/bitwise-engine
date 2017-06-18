#include <Catch/catch.hpp>

#include "bitwise/core/bit.h"

// -----------------------------------------------------------------------------
//  Constants
// -----------------------------------------------------------------------------
static const char* kTestTag = "[bit]";

// -----------------------------------------------------------------------------
//  Test cases
// -----------------------------------------------------------------------------
TEST_CASE("Single bitmask", kTestTag)
{
    REQUIRE(bw::bit::mask<uint8_t>(0) == static_cast<uint8_t>(1));
    REQUIRE(bw::bit::mask<uint8_t>(1) == static_cast<uint8_t>(2));
    REQUIRE(bw::bit::mask<uint8_t>(2) == static_cast<uint8_t>(4));
    REQUIRE(bw::bit::mask<uint8_t>(3) == static_cast<uint8_t>(8));
    REQUIRE(bw::bit::mask<uint8_t>(4) == static_cast<uint8_t>(16));
    REQUIRE(bw::bit::mask<uint8_t>(5) == static_cast<uint8_t>(32));
    REQUIRE(bw::bit::mask<uint8_t>(6) == static_cast<uint8_t>(64));
    REQUIRE(bw::bit::mask<uint8_t>(7) == static_cast<uint8_t>(128));
}

// -----------------------------------------------------------------------------

TEST_CASE("Variadic bitmask template", kTestTag)
{
    REQUIRE(bw::bit::mask<uint8_t>(0, 1, 2, 3, 4, 5, 6, 7) == static_cast<uint8_t>(255));
}