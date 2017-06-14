#include "bitwise/core/basic_types.h"

namespace bw
{

template <>
BW_API int btype::parse(const char* str)
{
    return -1;
}

template <>
BW_API bool btype::try_parse(const char* str, int& out)
{
    out = -1;
    return true;
}

template <>
BW_API const char* btype::to_string<int>(int type)
{
    return "";
}

}   // namespace bw