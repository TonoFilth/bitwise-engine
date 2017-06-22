#if !defined(BW_DOXYPRESS)
template<typename T, typename>
T bw::bit::mask<T>(uint8_t bit)
{
    BW_ASSERT(bit < sizeof(T) * 8, "Mask bit out of range. Bit=%hu Range=[0, %zu]", bit, sizeof(T) * 8 -1);

    return static_cast<T>(1) << bit;
}

// -----------------------------------------------------------------------------

template <typename T, typename ...Args, typename>
T bw::bit::mask<T>(uint8_t bit, Args&& ...args)
{
    BW_ASSERT(bit < sizeof(T) * 8, "Mask bit out of range. Bit=%hu Range=[0, %zu]", bit, sizeof(T) * 8 -1);

    return (static_cast<T>(1) << bit) | mask<T>(args...);
}

// -----------------------------------------------------------------------------

template<typename T, typename>
T bw::bit::set(T bits, uint8_t bit)
{
    BW_ASSERT(bit < sizeof(T) * 8, "Mask bit out of range. Bit=%hu Range=[0, %zu]", bit, sizeof(T) * 8 -1);

    return bits | (static_cast<T>(1) << bit);
}

// -----------------------------------------------------------------------------

template <typename T, typename>
T bw::bit::unset(T bits, uint8_t bit)
{
    BW_ASSERT(bit < sizeof(T) * 8, "Mask bit out of range. Bit=%hu Range=[0, %zu]", bit, sizeof(T) * 8 -1);

    return bits & ~(static_cast<T>(1) << bit);
}

// -----------------------------------------------------------------------------

template <typename T, typename>
T bw::bit::toggle(T bits, uint8_t bit)
{
    BW_ASSERT(bit < sizeof(T) * 8, "Mask bit out of range. Bit=%hu Range=[0, %zu]", bit, sizeof(T) * 8 -1);

    return is_set(bits, bit) ? unset(bits, bit) : set(bits, bit);
}

// -----------------------------------------------------------------------------

template <typename T, typename>
T bw::bit::complement(T bits)
{
    return ~bits;
}

// -----------------------------------------------------------------------------

template <typename T, typename>
bool bw::bit::is_set(T bits, uint8_t bit)
{
    BW_ASSERT(bit < sizeof(T) * 8, "Mask bit out of range. Bit=%hu Range=[0, %zu]", bit, sizeof(T) * 8 -1);

    return ((static_cast<T>(1) << bit) & bits) != 0;
}

// -----------------------------------------------------------------------------

template <typename T, typename>
void bw::bit::to_string(T bits, char* buffer, size_t bufferSize)
{
    BW_UNIMPLEMENTED();
}

#endif