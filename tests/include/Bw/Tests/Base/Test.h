#include <Catch/Catch.hpp>
#include "Bw/Base/Test.h"

TEST_CASE("Basic Test", "[base]")
{
	SECTION("Sum")
	{
		REQUIRE(bw::a_test_func(1, 2) == 3);
	}
}