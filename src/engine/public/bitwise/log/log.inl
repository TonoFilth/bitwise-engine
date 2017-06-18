template <typename ...Args>
const char* bw::internal::format_log_message(const char* format, Args&& ...args)
{
    static char message[bw::log::kMaxLogMessage];
    cstring::format(message, bw::log::kMaxLogMessage, format, std::forward<Args>(args)...);
    return message;
}