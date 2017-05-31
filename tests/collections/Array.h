#include <iostream>
#include <Catch/Catch.hpp>
#include <Bw/Base.h>
#include <Bw/Memory.h>
#include <Bw/Collections.h>

TEST_CASE("Array", "[collections]")
{
	using namespace bw;

	SECTION("Empty")
	{
		Array<int> a(Memory::GlobalAllocator());

		for (int i = 0; i < 100; ++i)
		{
			array::PushBack(a, i);
			REQUIRE(a[i] == i);
		}

		REQUIRE(array::Size(a) == 100);
	}
}