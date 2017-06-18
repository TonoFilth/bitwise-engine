#include <cstdio>   // sscanf

#include "bitwise/core/integer.h"
#include "bitwise/core/cstring.h"

// -----------------------------------------------------------------------------
//  Private functions
// -----------------------------------------------------------------------------
template <typename T>
BW_FORCE_INLINE static T parse_integer(const char* str, const char* format)
{
    T result;
    bw::cstring::scan_cformat(str, format, &result);
    return result;
}

// -----------------------------------------------------------------------------

template <typename T>
BW_FORCE_INLINE static bool try_parse_integer(const char* str, const char* format, T& out)
{
    return bw::cstring::scan_cformat(str, format, &out) == 1;
}

namespace bw
{

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

template <> BW_API bool integer::try_parse(const char* str, short&              out) { return try_parse_integer<short>             (str, "%hd", out);  }
template <> BW_API bool integer::try_parse(const char* str, int&                out) { return try_parse_integer<int>               (str, "%d",  out);  }
template <> BW_API bool integer::try_parse(const char* str, long&               out) { return try_parse_integer<long>              (str, "%ld",  out); }
template <> BW_API bool integer::try_parse(const char* str, long long&          out) { return try_parse_integer<long long>         (str, "%lld", out); }
template <> BW_API bool integer::try_parse(const char* str, unsigned short&     out) { return try_parse_integer<unsigned short>    (str, "%hu",  out); }
template <> BW_API bool integer::try_parse(const char* str, unsigned&           out) { return try_parse_integer<unsigned>          (str, "%u",   out); }
template <> BW_API bool integer::try_parse(const char* str, unsigned long&      out) { return try_parse_integer<unsigned long>     (str, "%lu",  out); }
template <> BW_API bool integer::try_parse(const char* str, unsigned long long& out) { return try_parse_integer<unsigned long long>(str, "%llu", out); }

// -----------------------------------------------------------------------------

template <> BW_API void integer::to_string(short              i, char* buf, size_t bufSize) { cstring::to_string(i, buf, bufSize); }
template <> BW_API void integer::to_string(int                i, char* buf, size_t bufSize) { cstring::to_string(i, buf, bufSize); }
template <> BW_API void integer::to_string(long               i, char* buf, size_t bufSize) { cstring::to_string(i, buf, bufSize); }
template <> BW_API void integer::to_string(long long          i, char* buf, size_t bufSize) { cstring::to_string(i, buf, bufSize); }
template <> BW_API void integer::to_string(unsigned short     i, char* buf, size_t bufSize) { cstring::to_string(i, buf, bufSize); }
template <> BW_API void integer::to_string(unsigned           i, char* buf, size_t bufSize) { cstring::to_string(i, buf, bufSize); }
template <> BW_API void integer::to_string(unsigned long      i, char* buf, size_t bufSize) { cstring::to_string(i, buf, bufSize); }
template <> BW_API void integer::to_string(unsigned long long i, char* buf, size_t bufSize) { cstring::to_string(i, buf, bufSize); }

}   // namespace bw