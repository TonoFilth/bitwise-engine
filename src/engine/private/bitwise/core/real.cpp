#include "bitwise/core/real.h"
#include "bitwise/core/cstring.h"

namespace bw
{

// -----------------------------------------------------------------------------
//  Public functions
// -----------------------------------------------------------------------------
template <> BW_API float       real::parse(const char* str) { float       r; bw::cstring::scan_format(str, "%f",  &r); return r; }
template <> BW_API double      real::parse(const char* str) { double      r; bw::cstring::scan_format(str, "%lf", &r); return r; }
template <> BW_API long double real::parse(const char* str) { long double r; bw::cstring::scan_format(str, "%Lf", &r); return r; }

// -----------------------------------------------------------------------------

template <> BW_API bool real::try_parse(const char* str, float&       out) { return bw::cstring::scan_format(str, "%f",  &out) == 1; }
template <> BW_API bool real::try_parse(const char* str, double&      out) { return bw::cstring::scan_format(str, "%lf", &out) == 1; }
template <> BW_API bool real::try_parse(const char* str, long double& out) { return bw::cstring::scan_format(str, "%Lf", &out) == 1; }

// -----------------------------------------------------------------------------

template <> BW_API void real::to_string(float       f, char* buf, size_t bufSize, const char* opts) { bw::cstring::format(buf, bufSize, "%f");  }
template <> BW_API void real::to_string(double      f, char* buf, size_t bufSize, const char* opts) { bw::cstring::format(buf, bufSize, "%lf"); }
template <> BW_API void real::to_string(long double f, char* buf, size_t bufSize, const char* opts) { bw::cstring::format(buf, bufSize, "%Lf"); }

}   // namespace bw