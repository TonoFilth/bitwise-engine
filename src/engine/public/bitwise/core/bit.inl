// -----------------------------------------------------------------------------
//  Inline functions
// -----------------------------------------------------------------------------
template<typename T, typename>
T bw::bit::mask(T bit)
{
    return static_cast<T>(1) << bit;
}

// -----------------------------------------------------------------------------

template<typename T, typename>
T bw::bit::set(T bits, uint8_t bit)
{
    return bits | (static_cast<T>(1) << bit);
}

// -----------------------------------------------------------------------------

template<typename T, typename>
T bw::bit::unset(T bits, uint8_t bit)
{
    return bits & ~(static_cast<T>(1) << bit);
}

// -----------------------------------------------------------------------------

template<typename T, typename>
T bw::bit::toggle(T bits, uint8_t bit)
{
    return is_set(bits, bit) ? unset(bits, bit) : set(bits, bit);
}

// -----------------------------------------------------------------------------

template<typename T, typename>
T bw::bit::complement(T bits)
{
    return ~bits;
}

// -----------------------------------------------------------------------------

template<typename T, typename>
bool bw::bit::is_set(T bits, uint8_t bit)
{
    return ((static_cast<T>(1) << bit) & bits) != 0;
}

// -----------------------------------------------------------------------------

template <typename T, typename>
BW_FORCE_INLINE const char* bw::bit::to_string(T bits)
{
    static char buffer[sizeof(size_t)+1];   // 1 extra bit needed for the null terminating character

    size_t size = sizeof(T) * 8;
    uint8_t bit = 0;
    char* c = buffer + size - 1;

    while (c >= buffer)
    {
        *(c--) = is_set(bits, bit++) ? '1' : '0';
    }

    buffer[size] = '\0';
    return buffer;
}

// -----------------------------------------------------------------------------

template <typename T, typename>
BW_FORCE_INLINE const char* bw::bit::to_string(char* buffer, size_t bufferSize, T bits)
{
    size_t size = sizeof(T) * 8;

    BW_ASSERT(bufferSize >= size + 1);

    uint8_t bit = 0;
    char* c = buffer + size - 1;

    while (c >= buffer)
    {
        *(c--) = is_set(bits, bit++) ? '1' : '0';
    }

    buffer[size] = '\0';
    return buffer;
}