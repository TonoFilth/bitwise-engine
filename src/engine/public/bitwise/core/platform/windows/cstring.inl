// -----------------------------------------------------------------------------
//  Inline functions
// -----------------------------------------------------------------------------
template <typename ...Args>
size_t bw::cstring::scan_cformat(const char* str, const char* format, Args&& ...args)
{
    return static_cast<size_t>(::sscanf_s(str, format, std::forward<Args>(args)...));
}