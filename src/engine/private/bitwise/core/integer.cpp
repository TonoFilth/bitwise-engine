#include "bitwise/core/integer.h"
#include "bitwise/core/cstring.h"

namespace bw
{

// -----------------------------------------------------------------------------
//  Public functions
// -----------------------------------------------------------------------------
template <> BW_API short              integer::parse(const char* str) { short              i; bw::cstring::scan_format(str, "%hd",  &i); return i; }
template <> BW_API int                integer::parse(const char* str) { int                i; bw::cstring::scan_format(str, "%d",   &i); return i; }
template <> BW_API long               integer::parse(const char* str) { long               i; bw::cstring::scan_format(str, "%ld",  &i); return i; }
template <> BW_API long long          integer::parse(const char* str) { long long          i; bw::cstring::scan_format(str, "%lld", &i); return i; }
template <> BW_API unsigned short     integer::parse(const char* str) { unsigned short     i; bw::cstring::scan_format(str, "%hu",  &i); return i; }
template <> BW_API unsigned           integer::parse(const char* str) { unsigned           i; bw::cstring::scan_format(str, "%u",   &i); return i; }
template <> BW_API unsigned long      integer::parse(const char* str) { unsigned long      i; bw::cstring::scan_format(str, "%lu",  &i); return i; }
template <> BW_API unsigned long long integer::parse(const char* str) { unsigned long long i; bw::cstring::scan_format(str, "%llu", &i); return i; }

// -----------------------------------------------------------------------------

template <> BW_API bool integer::try_parse(const char* str, short&              out) { return bw::cstring::scan_format(str, "%hd",  &out) == 1; }
template <> BW_API bool integer::try_parse(const char* str, int&                out) { return bw::cstring::scan_format(str, "%d",   &out) == 1; }
template <> BW_API bool integer::try_parse(const char* str, long&               out) { return bw::cstring::scan_format(str, "%ld",  &out) == 1; }
template <> BW_API bool integer::try_parse(const char* str, long long&          out) { return bw::cstring::scan_format(str, "%lld", &out) == 1; }
template <> BW_API bool integer::try_parse(const char* str, unsigned short&     out) { return bw::cstring::scan_format(str, "%hu",  &out) == 1; }
template <> BW_API bool integer::try_parse(const char* str, unsigned&           out) { return bw::cstring::scan_format(str, "%u",   &out) == 1; }
template <> BW_API bool integer::try_parse(const char* str, unsigned long&      out) { return bw::cstring::scan_format(str, "%lu",  &out) == 1; }
template <> BW_API bool integer::try_parse(const char* str, unsigned long long& out) { return bw::cstring::scan_format(str, "%llu", &out) == 1; }

// -----------------------------------------------------------------------------

template <> BW_API void integer::to_string(short              i, char* buf, size_t bufSize) { bw::cstring::format(buf, bufSize, "%hd",  i); }
template <> BW_API void integer::to_string(int                i, char* buf, size_t bufSize) { bw::cstring::format(buf, bufSize, "%d",   i); }
template <> BW_API void integer::to_string(long               i, char* buf, size_t bufSize) { bw::cstring::format(buf, bufSize, "%ld",  i); }
template <> BW_API void integer::to_string(long long          i, char* buf, size_t bufSize) { bw::cstring::format(buf, bufSize, "%lld", i); }
template <> BW_API void integer::to_string(unsigned short     i, char* buf, size_t bufSize) { bw::cstring::format(buf, bufSize, "%hu",  i); }
template <> BW_API void integer::to_string(unsigned           i, char* buf, size_t bufSize) { bw::cstring::format(buf, bufSize, "%u",   i); }
template <> BW_API void integer::to_string(unsigned long      i, char* buf, size_t bufSize) { bw::cstring::format(buf, bufSize, "%lu",  i); }
template <> BW_API void integer::to_string(unsigned long long i, char* buf, size_t bufSize) { bw::cstring::format(buf, bufSize, "%llu", i); }

}   // namespace bw