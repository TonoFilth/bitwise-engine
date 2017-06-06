#if defined(BW_PLATFORM_ANDROID)
#   include <stdarg.h> // va_list
#else
#   include <cstdarg>  // va_list
#endif

#include "bitwise/core/basic_types.h"
#include "bitwise/core/log.h"
#include "bitwise/core/console.h"
#include "bitwise/core/cstring.h"
#include "bitwise/core/bit.h"

namespace bw
{

// -----------------------------------------------------------------------------
//  Constants
// -----------------------------------------------------------------------------
static const size_t MAX_LOG_MESSAGE    = 4096;
static const size_t MAX_FORMAT_MESSAGE = 64;

// -----------------------------------------------------------------------------
//  Private variables
// -----------------------------------------------------------------------------
static char m_messageBuffer[MAX_LOG_MESSAGE];
static char m_formatBuffer[MAX_FORMAT_MESSAGE];
static int m_priority = LogPriority::eVERBOSE;
static uint32_t m_channelState = bit::mask((uint32_t) LogChannel::eSYSTEM) | bit::mask((uint32_t) LogChannel::eUSER);

static int      m_defaultUserPriority = LogPriority::eINFO;
static uint32_t m_defaultUserChannel  = LogChannel::eUSER;

// -----------------------------------------------------------------------------
//  Private functions
// -----------------------------------------------------------------------------
static BW_INLINE bool filter(uint8_t channel, int priority)
{
    return !(bit::is_set(m_channelState, channel) && priority >= m_priority);
}

// -----------------------------------------------------------------------------

static const char* get_format(int channel, int priority, const char* function, const char* file, int line)
{
    const char* priorityName = nullptr;
    
    switch ((LogPriority::Enum) priority)
    {
        case LogPriority::eVERBOSE : priorityName = "VERBOSE"; break;
        case LogPriority::eINFO    : priorityName = "INFO";    break;
        case LogPriority::eWARNING : priorityName = "WARNING"; break;
        case LogPriority::eERROR   : priorityName = "ERROR";   break;
        case LogPriority::eFATAL   : priorityName = "FATAL";   break;
    }

    cstring::format(m_formatBuffer, MAX_FORMAT_MESSAGE, "[%s] %%s\n", priorityName);

    return m_formatBuffer;
}

// -----------------------------------------------------------------------------

static void write_log_message(uint8_t channel, int priority, const char* function, const char* file, int line, const char* messageFormat, va_list args)
{
    cstring::format_va(m_messageBuffer, MAX_LOG_MESSAGE, messageFormat, args);

    const char* format = get_format(channel, priority, function, file, line);
    console::write_format(format, m_messageBuffer);
}

// -----------------------------------------------------------------------------
//  Public functions
// -----------------------------------------------------------------------------
void log::message(const char* function, const char* file, int line, const char* messageFormat, ...)
{
    if (!filter(m_defaultUserChannel, m_defaultUserPriority))
    {
        va_list args;
	    va_start(args, messageFormat);
        write_log_message(m_defaultUserChannel, m_defaultUserPriority, function, file, line, messageFormat, args);
        va_end(args);
    }
}

// -----------------------------------------------------------------------------

void log::message(uint8_t channel, int priority, const char* function, const char* file, int line, const char* messageFormat, ...)
{
    // Filter the message
    if (!filter(channel, priority))
    {
        va_list args;
	    va_start(args, messageFormat);
        write_log_message(channel, priority, function, file, line, messageFormat, args);
	    va_end(args);
    }
}

// -----------------------------------------------------------------------------

void log::enable_channel(uint8_t channel)
{
    m_channelState = bit::set(m_channelState, channel);
}

// -----------------------------------------------------------------------------

void log::disable_channel(uint8_t channel)
{
    m_channelState = bit::unset(m_channelState, channel);
}

// -----------------------------------------------------------------------------

bool log::channel_enabled(uint8_t channel)
{
    return bit::is_set(m_channelState, channel);
}

}	// namespace bw