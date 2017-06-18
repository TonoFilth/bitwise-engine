template <typename T, typename>
constexpr T bw::integer::min()
{
    return std::numeric_limits<T>::min();
}

// -----------------------------------------------------------------------------

template <typename T, typename>
constexpr T bw::integer::max()
{
    return std::numeric_limits<T>::max();
}