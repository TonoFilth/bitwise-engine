#include "bitwise/core/export.h"
#include "bitwise/core/basic_types.h"

namespace bw
{

////////////////////////////////////////////////////////////////////////////////
//  LogChannel
////////////////////////////////////////////////////////////////////////////////
struct LogChannel
{
    enum Enum
    {
        eSYSTEM = 0,

        eRESERVED0,
        eRESERVED1,
        eRESERVED2,
        eRESERVED3,
        eRESERVED4,
        eRESERVED5,
        eRESERVED6,
        eRESERVED7,
        eRESERVED8,
        eRESERVED9,

        eUSER
    };
};

////////////////////////////////////////////////////////////////////////////////
//  LogPriority
////////////////////////////////////////////////////////////////////////////////
struct LogPriority
{
    enum Enum
    {
        eVERBOSE,
        eINFO,
        eWARNING,
        eERROR,
        eFATAL
    };
};

namespace log
{
    const size_t kMaxChannels = sizeof(uint32_t) * 8;

    BW_API void message(const char* function, const char* file, int line, const char* messageFormat, ...);
    BW_API void message(uint8_t channel, int priority, const char* function, const char* file, int line, const char* messageFormat, ...);
    BW_API void enable_channel(uint8_t channel);
    BW_API void disable_channel(uint8_t channel);
    BW_API bool channel_enabled(uint8_t channel);

}   // namespace log
}	// namespace bw

#define BW_LOGGING

// -----------------------------------------------------------------------------
//  Macros
// -----------------------------------------------------------------------------
#if defined(BW_LOGGING)
    #define BW_LOG(format, ...)                  bw::log::message(__func__, __FILE__, __LINE__, format, __VA_ARGS__)
    #define BW_LOG_VERBOSE(channel, format, ...) bw::log::message(channel, bw::LogPriority::eVERBOSE, __func__, __FILE__, __LINE__, format, __VA_ARGS__)
    #define BW_LOG_INFO(channel, format, ...)    bw::log::message(channel, bw::LogPriority::eINFO,    __func__, __FILE__, __LINE__, format, __VA_ARGS__)
    #define BW_LOG_WARNING(channel, format, ...) bw::log::message(channel, bw::LogPriority::eWARNING, __func__, __FILE__, __LINE__, format, __VA_ARGS__)
    #define BW_LOG_ERROR(channel, format, ...)   bw::log::message(channel, bw::LogPriority::eERROR,   __func__, __FILE__, __LINE__, format, __VA_ARGS__)
    #define BW_LOG_FATAL(channel, format, ...)   bw::log::message(channel, bw::LogPriority::eFATAL,   __func__, __FILE__, __LINE__, format, __VA_ARGS__)
#else

#endif