#include "bitwise/core/assert.h"
#include "bitwise/core/console.h"
#include "bitwise/core/cstring.h"
#include "bitwise/core/bit.h"
#include "bitwise/log/log.h"
#include "bitwise/log/output.h"
#include "bitwise/log/internal.h"

// -----------------------------------------------------------------------------
//  Constants
// -----------------------------------------------------------------------------
static const size_t kMaxFormatBuffer  = 64;
static const size_t kMaxOutputBuffer  = 4096;
static const size_t kMaxMessageBuffer = kMaxOutputBuffer - kMaxFormatBuffer;
static const size_t kMaxChannelName   = 32;
static const size_t kMaxLogOutputs    = 4;

// -----------------------------------------------------------------------------
//  Private variables
// -----------------------------------------------------------------------------
static char m_formatBuffer [kMaxFormatBuffer];
static char m_messageBuffer[kMaxMessageBuffer];
static char m_outputBuffer [kMaxOutputBuffer];
static char m_channelNames [bw::log::kMaxChannels][kMaxChannelName];

// -----------------------------------------------------------------------------

static bw::LogPriority::Enum m_priority     = bw::LogPriority::eVERBOSE;
static uint32_t              m_channelState = 0;

// -----------------------------------------------------------------------------

static bw::LogChannel::Enum  m_defaultUserChannel  = bw::LogChannel::eUSER;
static bw::LogPriority::Enum m_defaultUserPriority = bw::LogPriority::eINFO;

// -----------------------------------------------------------------------------

static bw::LogOutput m_output[kMaxLogOutputs];

// -----------------------------------------------------------------------------
//  Private functions
// -----------------------------------------------------------------------------
static void default_output_function(const char* message, bw::LogChannel::Enum channel, bw::LogPriority::Enum priority, void* userData)
{
	if (priority < bw::LogPriority::eERROR)
	{
		bw::console::write(message);
	}
	else
	{
		bw::console::error::write(message);
	}
}

// -----------------------------------------------------------------------------

static BW_INLINE bool filter(bw::LogChannel::Enum channel, bw::LogPriority::Enum priority)
{
    return !(bw::bit::is_set(m_channelState, channel) && priority >= m_priority);
}

// -----------------------------------------------------------------------------

static const char* get_priority_name(bw::LogPriority::Enum priority)
{
    switch (priority)
    {
        case bw::LogPriority::eVERBOSE : return "VERBOSE";
        case bw::LogPriority::eINFO    : return "INFO";
        case bw::LogPriority::eWARNING : return "WARNING";
        case bw::LogPriority::eERROR   : return "ERROR";
        case bw::LogPriority::eFATAL   : return "FATAL";
    }

    BW_NO_ENTRY();
    return nullptr;
}

// -----------------------------------------------------------------------------

static const char* get_format(bw::LogChannel::Enum channel, bw::LogPriority::Enum priority, const char* function, const char* file, int line)
{
    bw::cstring::format(m_formatBuffer, kMaxFormatBuffer, "[%s] %%s\n", bw::log::channel_name(channel));
    return m_formatBuffer;
}

// -----------------------------------------------------------------------------

static void write_log_message(const char* message, bw::LogChannel::Enum channel, bw::LogPriority::Enum priority, const char* function, const char* file, int line)
{
    const char* format = get_format(channel, priority, function, file, line);
    bw::cstring::format(m_outputBuffer, kMaxOutputBuffer, format, message);

    bw::LogOutput* output = m_output;

    while (output != nullptr)
    {
        output->function(m_outputBuffer, channel, priority, output->userData);
        output = output->next;
    }
}

namespace bw
{

// -----------------------------------------------------------------------------
//  Internal functions
// -----------------------------------------------------------------------------
#if !defined(BW_DOXYPRESS)
void internal::log::initialize(int argc, char** argv)
{
    // Set engine channel names
    for (int i = 0; i < LogChannel::eUSER; ++i)
    {
        switch ((LogChannel::Enum) i)
        {
            case LogChannel::eSYSTEM    : bw::cstring::copy(m_channelNames[i], kMaxChannelName, "system");    break;
			case LogChannel::eNET       : bw::cstring::copy(m_channelNames[i], kMaxChannelName, "net");       break;
            case LogChannel::eRESERVED0 : bw::cstring::copy(m_channelNames[i], kMaxChannelName, "reserved0"); break;
            case LogChannel::eRESERVED1 : bw::cstring::copy(m_channelNames[i], kMaxChannelName, "reserved1"); break;
            case LogChannel::eRESERVED2 : bw::cstring::copy(m_channelNames[i], kMaxChannelName, "reserved2"); break;
            case LogChannel::eRESERVED3 : bw::cstring::copy(m_channelNames[i], kMaxChannelName, "reserved3"); break;
            case LogChannel::eRESERVED4 : bw::cstring::copy(m_channelNames[i], kMaxChannelName, "reserved4"); break;
            case LogChannel::eRESERVED5 : bw::cstring::copy(m_channelNames[i], kMaxChannelName, "reserved5"); break;
            case LogChannel::eRESERVED6 : bw::cstring::copy(m_channelNames[i], kMaxChannelName, "reserved6"); break;
            case LogChannel::eRESERVED7 : bw::cstring::copy(m_channelNames[i], kMaxChannelName, "reserved7"); break;

			default : BW_NO_ENTRY(); break;
        }
    }

    // Set default user channel names
    for (int i = LogChannel::eUSER; i < bw::log::kMaxChannels; ++i)
    {
        bw::cstring::format(m_channelNames[i], kMaxChannelName, "usr%d", i - LogChannel::eUSER);
    }

    bw::log::enable_channel(LogChannel::eSYSTEM);
	bw::log::enable_channel(LogChannel::eNET);
    bw::log::enable_channel(LogChannel::eUSER);

    bw::log::priority(LogPriority::eVERBOSE);

    // Default output function
    LogOutput* defaultOutput = m_output;

    defaultOutput->userData = nullptr;
    defaultOutput->next     = nullptr;
    defaultOutput->prev     = nullptr;
    defaultOutput->function = default_output_function;

}

// -----------------------------------------------------------------------------

void internal::log::shutdown()
{

}
#endif

////////////////////////////////////////////////////////////////////////////////
/// \details Detailed description.
/// \todo Write detailed description
////////////////////////////////////////////////////////////////////////////////
void log::message(const char* function, const char* file, int line, const char* format, ...)
{
    if (!filter(m_defaultUserChannel, m_defaultUserPriority))
    {
        va_list args;
	    va_start(args, format);

	    size_t nbChars = bw::cstring::format_va_list(m_messageBuffer, kMaxMessageBuffer, format, args);
	
	    va_end(args);

        write_log_message(m_messageBuffer, m_defaultUserChannel, m_defaultUserPriority, function, file, line);
    }
}

////////////////////////////////////////////////////////////////////////////////
/// \details Detailed description.
/// \todo Write detailed description
////////////////////////////////////////////////////////////////////////////////
void log::message(LogChannel::Enum channel, LogPriority::Enum priority, const char* function, const char* file, int line, const char* format, ...)
{
    // Filter the message
    if (!filter(channel, priority))
    {
        va_list args;
	    va_start(args, format);

	    size_t nbChars = bw::cstring::format_va_list(m_messageBuffer, kMaxMessageBuffer, format, args);
	
	    va_end(args);

        write_log_message(m_messageBuffer, channel, priority, function, file, line);
    }
}

////////////////////////////////////////////////////////////////////////////////
/// \details Detailed description.
/// \todo Write detailed description
////////////////////////////////////////////////////////////////////////////////
void log::enable_channel(LogChannel::Enum channel)
{
    m_channelState = bit::set(m_channelState, static_cast<uint8_t>(channel));
}

////////////////////////////////////////////////////////////////////////////////
/// \details Detailed description.
/// \todo Write detailed description
////////////////////////////////////////////////////////////////////////////////
void log::disable_channel(LogChannel::Enum channel)
{
    m_channelState = bit::unset(m_channelState, static_cast<uint8_t>(channel));
}

////////////////////////////////////////////////////////////////////////////////
/// \details Detailed description.
/// \todo Write detailed description
////////////////////////////////////////////////////////////////////////////////
bool log::channel_enabled(LogChannel::Enum channel)
{
    return bit::is_set(m_channelState, static_cast<uint8_t>(channel));
}

////////////////////////////////////////////////////////////////////////////////
/// \details Detailed description.
/// \todo Write detailed description
////////////////////////////////////////////////////////////////////////////////
const char* log::channel_name(LogChannel::Enum channel)
{
    BW_ASSERT(static_cast<size_t>(channel) < kMaxChannels, "Invalid channel '%hu'. Max channels %zu.", channel, kMaxChannels);
    return m_channelNames[channel];
}

////////////////////////////////////////////////////////////////////////////////
/// \details Detailed description.
/// \todo Write detailed description
////////////////////////////////////////////////////////////////////////////////
void log::channel_name(LogChannel::Enum channel, const char* name)
{
    BW_ASSERT(static_cast<size_t>(channel) < kMaxChannels, "Invalid channel '%hu'. Max channels %zu.", channel, kMaxChannels);
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