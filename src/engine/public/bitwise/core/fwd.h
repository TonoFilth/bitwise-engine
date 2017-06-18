#if !defined(BW_DOXYPRESS)

// -----------------------------------------------------------------------------
//  Forward declarations
// -----------------------------------------------------------------------------
namespace bw
{
namespace cstring
{
    template <typename T>
    void to_string(const T& value, char* buffer, size_t bufferSize, const char* formatOptions);

    template <typename ...Args>
    size_t format(char* buffer, size_t bufferSize, const char* format, Args&& ...args);

}   // namespace cstring
}   // namespace bw

#endif