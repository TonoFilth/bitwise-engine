template <typename T, typename>
constexpr T bw::real::min()
{
    return std::numeric_limits<T>::min();
}

// -----------------------------------------------------------------------------

template <typename T, typename>
constexpr T bw::real::max()
{
    return std::numeric_limits<T>::max();
}