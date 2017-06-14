template <typename ...Args>
void bw::console::write_format(const char* format, Args&& ...args)
{
    static char buffer[1024];

    bw::cstring::format(buffer, 1024, format, std::forward<Args>(args)...);
    write(buffer);
}