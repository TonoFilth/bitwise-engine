#include <cstring>
#include <Catch/catch.hpp>

#include "bitwise/core/integer.h"

// -----------------------------------------------------------------------------
//  Constants
// -----------------------------------------------------------------------------
static const size_t kBufferSize = std::numeric_limits<unsigned long long>::digits10 + 2;    // +1 precission bit + '\0'
static const char*  kTestTag    = "[integer]";

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

template <> const char* get_cformat(short)              { return "%hd";  }
template <> const char* get_cformat(int)                { return "%d";   }
template <> const char* get_cformat(long)               { return "%ld";  }
template <> const char* get_cformat(long long)          { return "%lld"; }
template <> const char* get_cformat(unsigned short)     { return "%hu";  }
template <> const char* get_cformat(unsigned)           { return "%u";   }
template <> const char* get_cformat(unsigned long)      { return "%lu";  }
template <> const char* get_cformat(unsigned long long) { return "%llu"; }

// -----------------------------------------------------------------------------

template <typename T>
static const char* get_cstr(T integer)
{
    sprintf_s(m_buffer, kBufferSize, get_cformat(integer), integer);
    return m_buffer;
}

// -----------------------------------------------------------------------------
//  Test cases
// -----------------------------------------------------------------------------
TEST_CASE("Integer limits", kTestTag)
{
    // Min
    REQUIRE(bw::integer::min<short>()              == SHRT_MIN);
    REQUIRE(bw::integer::min<int>()                == INT_MIN);
    REQUIRE(bw::integer::min<long>()               == LONG_MIN);
    REQUIRE(bw::integer::min<long long>()          == LLONG_MIN);
    REQUIRE(bw::integer::min<unsigned short>()     == 0);
    REQUIRE(bw::integer::min<unsigned>()           == 0);
    REQUIRE(bw::integer::min<unsigned long>()      == 0);
    REQUIRE(bw::integer::min<unsigned long long>() == 0);

    // Max
    REQUIRE(bw::integer::max<short>()              == SHRT_MAX);
    REQUIRE(bw::integer::max<int>()                == INT_MAX);
    REQUIRE(bw::integer::max<long>()               == LONG_MAX);
    REQUIRE(bw::integer::max<long long>()          == LLONG_MAX);
    REQUIRE(bw::integer::max<unsigned short>()     == USHRT_MAX);
    REQUIRE(bw::integer::max<unsigned>()           == UINT_MAX);
    REQUIRE(bw::integer::max<unsigned long>()      == ULONG_MAX);
    REQUIRE(bw::integer::max<unsigned long long>() == ULLONG_MAX);
}

// -----------------------------------------------------------------------------

TEST_CASE("Integer parse", kTestTag)
{
    REQUIRE(bw::integer::parse<short>             (get_cstr(SHRT_MAX))   == SHRT_MAX);
    REQUIRE(bw::integer::parse<int>               (get_cstr(INT_MAX))    == INT_MAX);
    REQUIRE(bw::integer::parse<long>              (get_cstr(LONG_MAX))   == LONG_MAX);
    REQUIRE(bw::integer::parse<long long>         (get_cstr(LLONG_MAX))  == LLONG_MAX);
    REQUIRE(bw::integer::parse<unsigned short>    (get_cstr(USHRT_MAX))  == USHRT_MAX);
    REQUIRE(bw::integer::parse<unsigned>          (get_cstr(UINT_MAX))   == UINT_MAX);
    REQUIRE(bw::integer::parse<unsigned long>     (get_cstr(ULONG_MAX))  == ULONG_MAX);
    REQUIRE(bw::integer::parse<unsigned long long>(get_cstr(ULLONG_MAX)) == ULLONG_MAX);
}

// -----------------------------------------------------------------------------

TEST_CASE("Integer try_parse", kTestTag)
{
    short              ishort    = 0;
    int                iint      = 0;
    long               ilong     = 0;
    long long          ilonglong = 0;
    unsigned short     ushort    = 0;
    unsigned           uint      = 0;
    unsigned long      ulong     = 0;
    unsigned long long ulonglong = 0;

    REQUIRE(bw::integer::try_parse<short>              (get_cstr(SHRT_MAX),   ishort));
    REQUIRE(bw::integer::try_parse<int>                (get_cstr(INT_MAX),    iint));
    REQUIRE(bw::integer::try_parse<long>               (get_cstr(LONG_MAX),   ilong));
    REQUIRE(bw::integer::try_parse<long long>          (get_cstr(LLONG_MAX),  ilonglong));
    REQUIRE(bw::integer::try_parse<unsigned short>     (get_cstr(USHRT_MAX),  ushort));
    REQUIRE(bw::integer::try_parse<unsigned>           (get_cstr(UINT_MAX),   uint));
    REQUIRE(bw::integer::try_parse<unsigned long>      (get_cstr(ULONG_MAX),  ulong));
    REQUIRE(bw::integer::try_parse<unsigned long long> (get_cstr(ULLONG_MAX), ulonglong));

    REQUIRE(ishort    == SHRT_MAX);
    REQUIRE(iint      == INT_MAX);
    REQUIRE(ilong     == LONG_MAX);
    REQUIRE(ilonglong == LLONG_MAX);
    REQUIRE(ushort    == USHRT_MAX);
    REQUIRE(uint      == UINT_MAX);
    REQUIRE(ulong     == ULONG_MAX);
    REQUIRE(ulonglong == ULLONG_MAX);
}

// -----------------------------------------------------------------------------

TEST_CASE("Integer to_string", kTestTag)
{
    char buffer[kBufferSize];
    
    // Min
    bw::integer::to_string(bw::integer::min<short>(),              buffer, kBufferSize); REQUIRE(strcmp(buffer, get_cstr(SHRT_MIN))  == 0);
    bw::integer::to_string(bw::integer::min<int>(),                buffer, kBufferSize); REQUIRE(strcmp(buffer, get_cstr(INT_MIN))   == 0);
    bw::integer::to_string(bw::integer::min<long>(),               buffer, kBufferSize); REQUIRE(strcmp(buffer, get_cstr(LONG_MIN))  == 0);
    bw::integer::to_string(bw::integer::min<long long>(),          buffer, kBufferSize); REQUIRE(strcmp(buffer, get_cstr(LLONG_MIN)) == 0);
    bw::integer::to_string(bw::integer::min<unsigned short>(),     buffer, kBufferSize); REQUIRE(strcmp(buffer, get_cstr(0))         == 0);
    bw::integer::to_string(bw::integer::min<unsigned>(),           buffer, kBufferSize); REQUIRE(strcmp(buffer, get_cstr(0))         == 0);
    bw::integer::to_string(bw::integer::min<unsigned long>(),      buffer, kBufferSize); REQUIRE(strcmp(buffer, get_cstr(0))         == 0);
    bw::integer::to_string(bw::integer::min<unsigned long long>(), buffer, kBufferSize); REQUIRE(strcmp(buffer, get_cstr(0))         == 0);

    // Max
    bw::integer::to_string(bw::integer::max<short>(),              buffer, kBufferSize); REQUIRE(strcmp(buffer, get_cstr(SHRT_MAX))   == 0);
    bw::integer::to_string(bw::integer::max<int>(),                buffer, kBufferSize); REQUIRE(strcmp(buffer, get_cstr(INT_MAX))    == 0);
    bw::integer::to_string(bw::integer::max<long>(),               buffer, kBufferSize); REQUIRE(strcmp(buffer, get_cstr(LONG_MAX))   == 0);
    bw::integer::to_string(bw::integer::max<long long>(),          buffer, kBufferSize); REQUIRE(strcmp(buffer, get_cstr(LLONG_MAX))  == 0);
    bw::integer::to_string(bw::integer::max<unsigned short>(),     buffer, kBufferSize); REQUIRE(strcmp(buffer, get_cstr(USHRT_MAX))  == 0);
    bw::integer::to_string(bw::integer::max<unsigned>(),           buffer, kBufferSize); REQUIRE(strcmp(buffer, get_cstr(UINT_MAX))   == 0);
    bw::integer::to_string(bw::integer::max<unsigned long>(),      buffer, kBufferSize); REQUIRE(strcmp(buffer, get_cstr(ULONG_MAX))  == 0);
    bw::integer::to_string(bw::integer::max<unsigned long long>(), buffer, kBufferSize); REQUIRE(strcmp(buffer, get_cstr(ULLONG_MAX)) == 0);
}