#include "bitwise/core/assert.h"
#include "bitwise/core/console.h"
#include "bitwise/core/cstring.h"
#include "bitwise/core/bit.h"
#include "bitwise/log/log.h"
#include "bitwise/log/internal.h"

// -----------------------------------------------------------------------------
//  Constants
// -----------------------------------------------------------------------------
static const size_t kMaxFormatMessage = 64;
static const size_t kMaxChannelName   = 32;

// -----------------------------------------------------------------------------
//  Private variables
// -----------------------------------------------------------------------------
static char m_formatBuffer[kMaxFormatMessage];
static bw::LogPriority::Enum m_priority     = bw::LogPriority::eVERBOSE;
static uint32_t m_channelState = 0x0;

static uint32_t              m_defaultUserChannel  = bw::LogChannel::eUSER;
static bw::LogPriority::Enum m_defaultUserPriority = bw::LogPriority::eINFO;

static char m_channelNames[bw::log::kMaxChannels][kMaxChannelName];

// -----------------------------------------------------------------------------
//  Private functions
// -----------------------------------------------------------------------------
static BW_INLINE bool filter(uint8_t channel, bw::LogPriority::Enum priority)
{
    return !(bw::bit::is_set(m_channelState, channel) && priority >= m_priority);
}

// -----------------------------------------------------------------------------

static const char* get_format(uint8_t channel, bw::LogPriority::Enum priority, const char* function, const char* file, int line)
{
    /*const char* priorityName = nullptr;
    
    switch (priority)
    {
        case LogPriority::eVERBOSE : priorityName = "VERBOSE"; break;
        case LogPriority::eINFO    : priorityName = "INFO";    break;
        case LogPriority::eWARNING : priorityName = "WARNING"; break;
        case LogPriority::eERROR   : priorityName = "ERROR";   break;
        case LogPriority::eFATAL   : priorityName = "FATAL";   break;
    }

    cstring::cformat(m_formatBuffer, kMaxFormatMessage, "[%s] %%s\n", priorityName);

    return m_formatBuffer;*/

    bw::cstring::cformat(m_formatBuffer, kMaxFormatMessage, "[%s] %%s\n", bw::log::channel_name(channel));

    return m_formatBuffer;
}

// -----------------------------------------------------------------------------

static void write_log_message(const char* message, uint8_t channel, bw::LogPriority::Enum priority, const char* function, const char* file, int line)
{
    const char* format = get_format(channel, priority, function, file, line);
    bw::console::write_cformat(format, message);
}

namespace bw
{

// -----------------------------------------------------------------------------
//  Public functions
// -----------------------------------------------------------------------------
#if !defined(BW_DOXYPRESS)
void log::initialize(int argc, char** argv)
{
    // Set engine channel names
    for (int i = 0; i < LogChannel::eUSER; ++i)
    {
        switch ((LogChannel::Enum) i)
        {
            case LogChannel::eSYSTEM    : cstring::copy(m_channelNames[i], kMaxChannelName, "system");    break;
            case LogChannel::eRESERVED0 : cstring::copy(m_channelNames[i], kMaxChannelName, "reserved0"); break;
            case LogChannel::eRESERVED1 : cstring::copy(m_channelNames[i], kMaxChannelName, "reserved1"); break;
            case LogChannel::eRESERVED2 : cstring::copy(m_channelNames[i], kMaxChannelName, "reserved2"); break;
            case LogChannel::eRESERVED3 : cstring::copy(m_channelNames[i], kMaxChannelName, "reserved3"); break;
            case LogChannel::eRESERVED4 : cstring::copy(m_channelNames[i], kMaxChannelName, "reserved4"); break;
            case LogChannel::eRESERVED5 : cstring::copy(m_channelNames[i], kMaxChannelName, "reserved5"); break;
            case LogChannel::eRESERVED6 : cstring::copy(m_channelNames[i], kMaxChannelName, "reserved6"); break;
            case LogChannel::eRESERVED7 : cstring::copy(m_channelNames[i], kMaxChannelName, "reserved7"); break;
        }
    }

    // Set default user channel names
    for (int i = LogChannel::eUSER; i < kMaxChannels; ++i)
    {
        cstring::cformat(m_channelNames[i], kMaxChannelName, "usr%d", i - LogChannel::eUSER);
    }

    enable_channel(LogChannel::eSYSTEM);
    enable_channel(LogChannel::eUSER);

    priority(LogPriority::eVERBOSE);
}

// -----------------------------------------------------------------------------

void log::shutdown()
{

}
#endif

////////////////////////////////////////////////////////////////////////////////
/// \details Detailed description.
/// \todo Write detailed description
////////////////////////////////////////////////////////////////////////////////
void log::message(const char* message, const char* function, const char* file, int line)
{
    if (!filter(m_defaultUserChannel, m_defaultUserPriority))
    {
        write_log_message(message, m_defaultUserChannel, m_defaultUserPriority, function, file, line);
    }
}

////////////////////////////////////////////////////////////////////////////////
/// \details Detailed description.
/// \todo Write detailed description
////////////////////////////////////////////////////////////////////////////////
void log::message(const char* message, uint8_t channel, LogPriority::Enum priority, const char* function, const char* file, int line)
{
    // Filter the message
    if (!filter(channel, priority))
    {
        write_log_message(message, channel, priority, function, file, line);
    }
}

////////////////////////////////////////////////////////////////////////////////
/// \details Detailed description.
/// \todo Write detailed description
////////////////////////////////////////////////////////////////////////////////
void log::enable_channel(uint8_t channel)
{
    m_channelState = bit::set(m_channelState, channel);
}

////////////////////////////////////////////////////////////////////////////////
/// \details Detailed description.
/// \todo Write detailed description
////////////////////////////////////////////////////////////////////////////////
void log::disable_channel(uint8_t channel)
{
    m_channelState = bit::unset(m_channelState, channel);
}

////////////////////////////////////////////////////////////////////////////////
/// \details Detailed description.
/// \todo Write detailed description
////////////////////////////////////////////////////////////////////////////////
bool log::channel_enabled(uint8_t channel)
{
    return bit::is_set(m_channelState, channel);
}

////////////////////////////////////////////////////////////////////////////////
/// \details Detailed description.
/// \todo Write detailed description
////////////////////////////////////////////////////////////////////////////////
const char* log::channel_name(uint8_t channel)
{
    BW_ASSERT(channel < kMaxChannels);
    return m_channelNames[channel];
}

////////////////////////////////////////////////////////////////////////////////
/// \details Detailed description.
/// \todo Write detailed description
////////////////////////////////////////////////////////////////////////////////
void log::channel_name(uint8_t channel, const char* name)
{
    BW_ASSERT(channel < kMaxChannels);
    cstring::copy(m_channelNames[channel], kMaxChannelName, name);
}

////////////////////////////////////////////////////////////////////////////////
/// \details Detailed description.
/// \todo Write detailed description
////////////////////////////////////////////////////////////////////////////////
LogPriority::Enum log::priority()
{
    return m_priority;
}

////////////////////////////////////////////////////////////////////////////////
/// \details Detailed description.
/// \todo Write detailed description
////////////////////////////////////////////////////////////////////////////////
LogPriority::Enum log::priority(LogPriority::Enum newPriority)
{
    LogPriority::Enum prevPriority = m_priority;
    m_priority = newPriority;

    return prevPriority;
}

}	// namespace bw