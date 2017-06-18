#include "bitwise/core/cstring.h"
#include "bitwise/core/bit.h"

// -----------------------------------------------------------------------------
//  Private functions
// -----------------------------------------------------------------------------
template <typename T>
static void bits_to_str(T bits, char* buf, size_t bufSize)
{
    size_t size = sizeof(T) * 8;

    BW_ASSERT(bufSize >= size + 1);

    uint8_t bit = 0;
    char* c = buf + size - 1;

    while (c >= buf)
    {
        *(c--) = bw::bit::is_set(bits, bit++) ? '1' : '0';
    }

    buf[size] = '\0';
}

// -----------------------------------------------------------------------------

template <typename T>
static void char_to_str(T c, char* buf, size_t bufSize, const char* opts)
{
    BW_ASSERT(bufSize >= 2);

    switch (*opts)
    {
        case 'b' : bits_to_str(c, buf, bufSize);                 break;
        case 'n' : bw::cstring::cformat(buf, bufSize, "%hu", c); break;

        default :
        {
            *buf++ = c;
            *buf   = '\0';
            break;
        }
    }
}

// -----------------------------------------------------------------------------

template <typename T>
static void integer_to_str(T integer, const char* format, char* buf, size_t bufSize, const char* opts)
{
    switch (*opts)
    {
        case 'b' : bits_to_str(integer, buf, bufSize); break;

        default : bw::cstring::cformat(buf, bufSize, format, integer); break;
    }
}

// -----------------------------------------------------------------------------

template <typename T>
static BW_FORCE_INLINE void real_to_str(T real, const char* format, char* buf, size_t bufSize, const char* opts)
{
    switch (*opts)
    {
        case 'b' :
        {
            switch (sizeof(T))
            {
                case 4 : bits_to_str(*reinterpret_cast<uint32_t*>(&real), buf, bufSize); break;
                case 8 : bits_to_str(*reinterpret_cast<uint64_t*>(&real), buf, bufSize); break;

                default: bw::cstring::copy(buf, bufSize, "<unknown_size>"); break;
            }

            break;
        }

        default : bw::cstring::cformat(buf, bufSize, format, real); break;
    }

    if (bw::cstring::starts_with(opts, "e"))
    {
        char f[4];
        
        bw::cstring::copy(f, 4, format);
        bw::cstring::replace(f, 'f', 'e');
        bw::cstring::cformat(buf, bufSize, f, real);
    }
}

namespace bw
{

// -----------------------------------------------------------------------------
//  Integer number conversions
// -----------------------------------------------------------------------------
template <> BW_API void cstring::to_string(const short&              i, char* buf, size_t bufSize, const char* opts) { integer_to_str(i, "%hd",  buf, bufSize, opts); }
template <> BW_API void cstring::to_string(const int&                i, char* buf, size_t bufSize, const char* opts) { integer_to_str(i, "%d",   buf, bufSize, opts); }
template <> BW_API void cstring::to_string(const long&               i, char* buf, size_t bufSize, const char* opts) { integer_to_str(i, "%ld",  buf, bufSize, opts); }
template <> BW_API void cstring::to_string(const long long&          i, char* buf, size_t bufSize, const char* opts) { integer_to_str(i, "%lld", buf, bufSize, opts); }
template <> BW_API void cstring::to_string(const unsigned short&     i, char* buf, size_t bufSize, const char* opts) { integer_to_str(i, "%hu",  buf, bufSize, opts); }
template <> BW_API void cstring::to_string(const unsigned&           i, char* buf, size_t bufSize, const char* opts) { integer_to_str(i, "%u",   buf, bufSize, opts); }
template <> BW_API void cstring::to_string(const unsigned long&      i, char* buf, size_t bufSize, const char* opts) { integer_to_str(i, "%lu",  buf, bufSize, opts); }
template <> BW_API void cstring::to_string(const unsigned long long& i, char* buf, size_t bufSize, const char* opts) { integer_to_str(i, "%llu", buf, bufSize, opts); }

// -----------------------------------------------------------------------------
//  Real number conversions
// -----------------------------------------------------------------------------
template <> BW_API void cstring::to_string(const float&       r, char* buf, size_t bufSize, const char* opts) { real_to_str(r, "%f",  buf, bufSize, opts); }
template <> BW_API void cstring::to_string(const double&      r, char* buf, size_t bufSize, const char* opts) { real_to_str(r, "%lf", buf, bufSize, opts); }
template <> BW_API void cstring::to_string(const long double& r, char* buf, size_t bufSize, const char* opts) { real_to_str(r, "%Lf", buf, bufSize, opts); }

// -----------------------------------------------------------------------------
//  Character conversions
// -----------------------------------------------------------------------------
template <>
BW_API void cstring::to_string(const char& c, char* buf, size_t bufSize, const char* opts)
{
    char_to_str(c, buf, bufSize, opts);
}

// -----------------------------------------------------------------------------

template <>
BW_API void cstring::to_string(const signed char& c, char* buf, size_t bufSize, const char* opts)
{
    char_to_str(c, buf, bufSize, opts);
}

// -----------------------------------------------------------------------------

template <>
BW_API void cstring::to_string(const unsigned char& c, char* buf, size_t bufSize, const char* opts)
{
    char_to_str(c, buf, bufSize, opts);
}

// -----------------------------------------------------------------------------

template <>
BW_API void cstring::to_string(const char* str, char* buf, size_t bufSize, const char* opts)
{
    copy(buf, bufSize, str);
}

// -----------------------------------------------------------------------------
//  Other conversions
// -----------------------------------------------------------------------------
template <>
BW_API void cstring::to_string(const bool& b, char* buf, size_t bufSize, const char* opts)
{
    char o = *opts;

    switch (o)
    {
        case 's' : copy(buf, bufSize, b ? "t"    : "f");     break;
        case 'S' : copy(buf, bufSize, b ? "T"    : "F");     break;
        case 'n' : copy(buf, bufSize, b ? "1"    : "0");     break;
        case 'U' : copy(buf, bufSize, b ? "TRUE" : "FALSE"); break;

        default : copy(buf, bufSize, b ? "true" : "false");
    }
}

// -----------------------------------------------------------------------------

template <>
BW_API void cstring::to_string(const nullptr_t& value, char* buffer, size_t bufferSize, const char* formatOptions)
{
    copy(buffer, bufferSize, "null");
}

// -----------------------------------------------------------------------------

template <>
BW_API void cstring::to_string(const void* pointer, char* buf, size_t bufSize, const char* opts)
{
    cformat(buf, bufSize, "%p", pointer);
}

}   // namespace bw