#pragma once

#include "bitwise/core/macros.h"
#include "bitwise/log/channel.h"
#include "bitwise/log/priority.h"

namespace bw
{
////////////////////////////////////////////////////////////////////////////////
/// \brief Brief description.
/// \todo Write brief description
////////////////////////////////////////////////////////////////////////////////
namespace log
{
    const size_t kMaxChannels     = sizeof(uint32_t) * 8;               ///< TODO
    const size_t kMaxUserChannels = kMaxChannels - LogChannel::eUSER;   ///< TODO
    const size_t kMaxLogMessage   = 4096;                               ///< TODO

	////////////////////////////////////////////////////////////////////////////
	/// \brief Brief description.
	/// \todo Write brief description.
	////////////////////////////////////////////////////////////////////////////
    BW_API void message(const char* function, const char* file, int line, const char* format, ...);

	////////////////////////////////////////////////////////////////////////////
	/// \brief Brief description.
	/// \todo Write brief description.
	////////////////////////////////////////////////////////////////////////////
    BW_API void message(LogChannel::Enum channel, LogPriority::Enum priority, const char* function, const char* file, int line, const char* format, ...);

	////////////////////////////////////////////////////////////////////////////
	/// \brief Brief description.
	/// \todo Write brief description.
	////////////////////////////////////////////////////////////////////////////
    BW_API void enable_channel(LogChannel::Enum channel);

	////////////////////////////////////////////////////////////////////////////
	/// \brief Brief description.
	/// \todo Write brief description.
	////////////////////////////////////////////////////////////////////////////
    BW_API void disable_channel(LogChannel::Enum channel);

	////////////////////////////////////////////////////////////////////////////
	/// \brief Brief description.
	/// \todo Write brief description.
	////////////////////////////////////////////////////////////////////////////
    BW_API bool channel_enabled(LogChannel::Enum channel);

	////////////////////////////////////////////////////////////////////////////
	/// \brief Brief description.
	/// \todo Write brief description.
	////////////////////////////////////////////////////////////////////////////
    BW_API const char* channel_name(LogChannel::Enum channel);

	////////////////////////////////////////////////////////////////////////////
	/// \brief Brief description.
	/// \todo Write brief description.
	////////////////////////////////////////////////////////////////////////////
    BW_API void channel_name(LogChannel::Enum channel, const char* name);

    ////////////////////////////////////////////////////////////////////////////
	/// \brief Brief description.
	/// \todo Write brief description.
	////////////////////////////////////////////////////////////////////////////
    BW_API LogPriority::Enum priority();

    ////////////////////////////////////////////////////////////////////////////
	/// \brief Brief description.
	/// \todo Write brief description.
	////////////////////////////////////////////////////////////////////////////
    BW_API LogPriority::Enum priority(LogPriority::Enum newPriority);

}   // namespace log
}	// namespace bw

#define BW_LOGGING

// -----------------------------------------------------------------------------
//  Macros
// -----------------------------------------------------------------------------
#if defined(BW_LOGGING)
    #define BW_LOG(format, ...)                  { bw::log::message(__func__, __FILE__, __LINE__, format, __VA_ARGS__);                                     }
    #define BW_LOG_VERBOSE(channel, format, ...) { bw::log::message(channel, bw::LogPriority::eVERBOSE, __func__, __FILE__, __LINE__, format, __VA_ARGS__); }
    #define BW_LOG_INFO(channel, format, ...)    { bw::log::message(channel, bw::LogPriority::eINFO,    __func__, __FILE__, __LINE__, format, __VA_ARGS__); }
    #define BW_LOG_WARNING(channel, format, ...) { bw::log::message(channel, bw::LogPriority::eWARNING, __func__, __FILE__, __LINE__, format, __VA_ARGS__); }
    #define BW_LOG_ERROR(channel, format, ...)   { bw::log::message(channel, bw::LogPriority::eERROR,   __func__, __FILE__, __LINE__, format, __VA_ARGS__); }
    #define BW_LOG_FATAL(channel, format, ...)   { bw::log::message(channel, bw::LogPriority::eFATAL,   __func__, __FILE__, __LINE__, format, __VA_ARGS__); }
#else
    #define BW_LOG(format, ...)
    #define BW_LOG_VERBOSE(channel, format, ...)
    #define BW_LOG_INFO(channel, format, ...)
    #define BW_LOG_WARNING(channel, format, ...)
    #define BW_LOG_ERROR(channel, format, ...)
    #define BW_LOG_FATAL(channel, format, ...)
#endif

////////////////////////////////////////////////////////////////////////////////
/// \namespace bw::log
/// \ingroup log
///
/// \details Detailed description.
/// \todo Write detailed description
////////////////////////////////////////////////////////////////////////////////