#include <cstdio>   // sscanf

#include "bitwise/core/integer.h"
#include "bitwise/core/cstring.h"

namespace bw
{

// -----------------------------------------------------------------------------
//  Constants
// -----------------------------------------------------------------------------
static const size_t kStrBufferMax = 512;

// -----------------------------------------------------------------------------
//  Private variables
// -----------------------------------------------------------------------------
static char m_strBuffer[kStrBufferMax];

// -----------------------------------------------------------------------------
//  Private functions
// -----------------------------------------------------------------------------
template <typename T>
BW_FORCE_INLINE static T parse_integer(const char* str, const char* format)
{
    T result;
    cstring::scan_cformat(str, format, &result);
    return result;
}

// -----------------------------------------------------------------------------

template <typename T>
BW_FORCE_INLINE static bool try_parse_integer(const char* str, const char* format, T& out)
{
    return cstring::scan_cformat(str, format, &out) == 1;
}

// -----------------------------------------------------------------------------
//  Public functions
// -----------------------------------------------------------------------------
template <> BW_API short              integer::parse(const char* str) { return parse_integer<short>             (str, "%hd");  }
template <> BW_API int                integer::parse(const char* str) { return parse_integer<int>               (str, "%d");   }
template <> BW_API long               integer::parse(const char* str) { return parse_integer<long>              (str, "%ld");  }
template <> BW_API long long          integer::parse(const char* str) { return parse_integer<long long>         (str, "%lld"); }
template <> BW_API unsigned short     integer::parse(const char* str) { return parse_integer<unsigned short>    (str, "%hu");  }
template <> BW_API unsigned           integer::parse(const char* str) { return parse_integer<unsigned>          (str, "%u");   }
template <> BW_API unsigned long      integer::parse(const char* str) { return parse_integer<unsigned long>     (str, "%lu");  }
template <> BW_API unsigned long long integer::parse(const char* str) { return parse_integer<unsigned long long>(str, "%llu"); }

// -----------------------------------------------------------------------------

template <> BW_API bool integer::try_parse(const char* str, int& out) { return try_parse_integer(str, "%d", out); }

}   // namespace bw