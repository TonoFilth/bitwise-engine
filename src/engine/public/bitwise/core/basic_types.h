#pragma once

#include <limits>
#include <cstdint>

#include "bitwise/core/macros.h"

namespace bw
{
namespace btype
{
    template <typename T>
    static constexpr T min();

    template <typename T>
    static constexpr T epsilon();

    template <typename T>
    BW_API T parse(const char* str);

    template <typename T>
    BW_API bool try_parse(const char* str, T& out);

    template <typename T>
    BW_API const char* to_string(T in);

}   // namespace btype
}   // namespace bw

template <typename T>
constexpr T bw::btype::min()
{
    return std::numeric_limits<T>::min();
}

template <typename T>
constexpr T bw::btype::epsilon()
{
    return std::numeric_limits<T>::epsilon();
}