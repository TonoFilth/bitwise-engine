#include <cstring>
#include <Catch/catch.hpp>

#include "bitwise/core/real.h"

// -----------------------------------------------------------------------------
//  Constants
// -----------------------------------------------------------------------------
static const size_t kBufferSize = 512;
static const char*  kTestTag    = "[real]";

// -----------------------------------------------------------------------------
//  Private variables
// -----------------------------------------------------------------------------
static char m_buffer[kBufferSize];

// -----------------------------------------------------------------------------
//  Private functions
// -----------------------------------------------------------------------------
template <typename T>
static const char* get_cformat(T);

// -----------------------------------------------------------------------------

template <> const char* get_cformat(float)       { return "%e";  }
template <> const char* get_cformat(double)      { return "%le"; }
template <> const char* get_cformat(long double) { return "%Le"; }

// -----------------------------------------------------------------------------

template <typename T>
static const char* get_cstr(T real)
{
    sprintf_s(m_buffer, kBufferSize, get_cformat(real), real);
    return m_buffer;
}

// -----------------------------------------------------------------------------
//  Test cases
// -----------------------------------------------------------------------------
TEST_CASE("Real limits", kTestTag)
{
    // Min
    REQUIRE(bw::real::min<float>()       == FLT_MIN);
    REQUIRE(bw::real::min<double>()      == DBL_MIN);
    REQUIRE(bw::real::min<long double>() == LDBL_MIN);
    
    // Max
    REQUIRE(bw::real::max<float>()       == FLT_MAX);
    REQUIRE(bw::real::max<double>()      == DBL_MAX);
    REQUIRE(bw::real::max<long double>() == LDBL_MAX);
}

// -----------------------------------------------------------------------------

TEST_CASE("Real parse", kTestTag)
{
    float f = bw::real::parse<float>      (get_cstr(FLT_MAX));
    float f2 = FLT_MAX;

    REQUIRE(bw::real::parse<float>      (get_cstr(FLT_MAX))  == FLT_MAX);
    REQUIRE(bw::real::parse<double>     (get_cstr(DBL_MAX))  == DBL_MAX);
    REQUIRE(bw::real::parse<long double>(get_cstr(LDBL_MAX)) == LDBL_MAX);
}

// -----------------------------------------------------------------------------

TEST_CASE("Real try_parse", kTestTag)
{
    float       rfloat      = 0.0f;
    double      rdouble     = 0.0;
    long double rlongdouble = 0.0L;

    REQUIRE(bw::real::try_parse<float>      (get_cstr(FLT_MAX),  rfloat));
    REQUIRE(bw::real::try_parse<double>     (get_cstr(DBL_MAX),  rdouble));
    REQUIRE(bw::real::try_parse<long double>(get_cstr(LDBL_MAX), rlongdouble));

    REQUIRE(rfloat      == FLT_MAX);
    REQUIRE(rdouble     == DBL_MAX);
    REQUIRE(rlongdouble == LDBL_MAX);
}

// -----------------------------------------------------------------------------

TEST_CASE("Real to_string", kTestTag)
{
    char buffer[kBufferSize];
    
    // Min
    bw::real::to_string(bw::real::min<float>(),       buffer, kBufferSize, "e"); REQUIRE(strcmp(buffer, get_cstr(FLT_MIN))  == 0);
    bw::real::to_string(bw::real::min<double>(),      buffer, kBufferSize, "e"); REQUIRE(strcmp(buffer, get_cstr(DBL_MIN))  == 0);
    bw::real::to_string(bw::real::min<long double>(), buffer, kBufferSize, "e"); REQUIRE(strcmp(buffer, get_cstr(LDBL_MIN)) == 0);

    // Max
    bw::real::to_string(bw::real::max<float>(),       buffer, kBufferSize, "e"); REQUIRE(strcmp(buffer, get_cstr(FLT_MAX))  == 0);
    bw::real::to_string(bw::real::max<double>(),      buffer, kBufferSize, "e"); REQUIRE(strcmp(buffer, get_cstr(DBL_MAX))  == 0);
    bw::real::to_string(bw::real::max<long double>(), buffer, kBufferSize, "e"); REQUIRE(strcmp(buffer, get_cstr(LDBL_MAX)) == 0);
}