#include <Catch/Catch.hpp>
#include <Bw/Base/Endianness.h>

#define BW_TEST_VALUE 10

using namespace bw;

TEST_CASE("Endian Swap", "[base]")
{
	SECTION("Unsigned integers")
	{
		U16 u16 = BW_SWAP_16(static_cast<U16>(BW_TEST_VALUE));
		U32 u32 = BW_SWAP_32(static_cast<U32>(BW_TEST_VALUE));
		U64 u64 = BW_SWAP_64(static_cast<U64>(BW_TEST_VALUE));

		REQUIRE(BW_SWAP_16(u16) == BW_TEST_VALUE);
		REQUIRE(BW_SWAP_32(u32) == BW_TEST_VALUE);
		REQUIRE(BW_SWAP_64(u64) == BW_TEST_VALUE);
	}

	SECTION("Signed integers")
	{
		I16 i16 = BW_SWAP_16(static_cast<I16>(BW_TEST_VALUE));
		I32 i32 = BW_SWAP_32(static_cast<I32>(BW_TEST_VALUE));
		I64 i64 = BW_SWAP_64(static_cast<I64>(BW_TEST_VALUE));

		REQUIRE(BW_SWAP_16(i16) == BW_TEST_VALUE);
		REQUIRE(BW_SWAP_32(i32) == BW_TEST_VALUE);
		REQUIRE(BW_SWAP_64(i64) == BW_TEST_VALUE);
	}

	SECTION("Floating point")
	{
		F32 f32 = BW_SWAP_F32(static_cast<F32>(BW_TEST_VALUE));
		F64 f64 = BW_SWAP_F64(static_cast<F64>(BW_TEST_VALUE));

		REQUIRE(BW_SWAP_F32(f32) == static_cast<F32>(BW_TEST_VALUE));
		REQUIRE(BW_SWAP_F64(f64) == static_cast<F64>(BW_TEST_VALUE));
	}
}