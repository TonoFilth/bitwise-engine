#include <cstdio>   // sscanf

#include "bitwise/core/real.h"
#include "bitwise/core/cstring.h"

// -----------------------------------------------------------------------------
//  Private functions
// -----------------------------------------------------------------------------
template <typename T>
BW_FORCE_INLINE static T parse_real(const char* str, const char* format)
{
    T result;
    bw::cstring::scan_cformat(str, format, &result);
    return result;
}

// -----------------------------------------------------------------------------

template <typename T>
BW_FORCE_INLINE static bool try_parse_real(const char* str, const char* format, T& out)
{
    return bw::cstring::scan_cformat(str, format, &out) == 1;
}

namespace bw
{

// -----------------------------------------------------------------------------
//  Public functions
// -----------------------------------------------------------------------------
template <> BW_API float       real::parse(const char* str) { return parse_real<float>      (str, "%f");  }
template <> BW_API double      real::parse(const char* str) { return parse_real<double>     (str, "%lf"); }
template <> BW_API long double real::parse(const char* str) { return parse_real<long double>(str, "%Lf"); }

// -----------------------------------------------------------------------------

template <> BW_API bool real::try_parse(const char* str, float&       out) { return try_parse_real<float>      (str, "%f",  out); }
template <> BW_API bool real::try_parse(const char* str, double&      out) { return try_parse_real<double>     (str, "%lf", out); }
template <> BW_API bool real::try_parse(const char* str, long double& out) { return try_parse_real<long double>(str, "%Lf", out); }

// -----------------------------------------------------------------------------

template <> BW_API void real::to_string(float       f, char* buf, size_t bufSize, const char* opts) { cstring::to_string(f, buf, bufSize, opts); }
template <> BW_API void real::to_string(double      f, char* buf, size_t bufSize, const char* opts) { cstring::to_string(f, buf, bufSize, opts); }
template <> BW_API void real::to_string(long double f, char* buf, size_t bufSize, const char* opts) { cstring::to_string(f, buf, bufSize, opts); }

}   // namespace bw