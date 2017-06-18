#pragma once

#include <utility>  // forward

#include "bitwise/core/macros.h"
#include "bitwise/core/fwd.h"
#include "bitwise/log/log_channel.h"
#include "bitwise/log/log_priority.h"

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
    BW_API void message(const char* message, const char* function, const char* file, int line);

	////////////////////////////////////////////////////////////////////////////
	/// \brief Brief description.
	/// \todo Write brief description.
	////////////////////////////////////////////////////////////////////////////
    BW_API void message(const char* message, uint8_t channel, LogPriority::Enum priority, const char* function, const char* file, int line);

	////////////////////////////////////////////////////////////////////////////
	/// \brief Brief description.
	/// \todo Write brief description.
	////////////////////////////////////////////////////////////////////////////
    BW_API void enable_channel(uint8_t channel);

	////////////////////////////////////////////////////////////////////////////
	/// \brief Brief description.
	/// \todo Write brief description.
	////////////////////////////////////////////////////////////////////////////
    BW_API void disable_channel(uint8_t channel);

	////////////////////////////////////////////////////////////////////////////
	/// \brief Brief description.
	/// \todo Write brief description.
	////////////////////////////////////////////////////////////////////////////
    BW_API bool channel_enabled(uint8_t channel);

	////////////////////////////////////////////////////////////////////////////
	/// \brief Brief description.
	/// \todo Write brief description.
	////////////////////////////////////////////////////////////////////////////
    BW_API const char* channel_name(uint8_t channel);

	////////////////////////////////////////////////////////////////////////////
	/// \brief Brief description.
	/// \todo Write brief description.
	////////////////////////////////////////////////////////////////////////////
    BW_API void channel_name(uint8_t channel, const char* name);

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

namespace internal
{
    template <typename ...Args>
    BW_FORCE_INLINE BW_API const char* format_log_message(const char* format, Args&& ...args);

}   // namespace internal
}	// namespace bw

#include "bitwise/log/log.inl"

#define BW_LOGGING

// -----------------------------------------------------------------------------
//  Macros
// -----------------------------------------------------------------------------
#if defined(BW_LOGGING)
    #define BW_LOG(format, ...)                  { bw::log::message(bw::internal::format_log_message(format, __VA_ARGS__), __func__, __FILE__, __LINE__);                                     }
    #define BW_LOG_VERBOSE(channel, format, ...) { bw::log::message(bw::internal::format_log_message(format, __VA_ARGS__), channel, bw::LogPriority::eVERBOSE, __func__, __FILE__, __LINE__); }
    #define BW_LOG_INFO(channel, format, ...)    { bw::log::message(bw::internal::format_log_message(format, __VA_ARGS__), channel, bw::LogPriority::eINFO,    __func__, __FILE__, __LINE__); }
    #define BW_LOG_WARNING(channel, format, ...) { bw::log::message(bw::internal::format_log_message(format, __VA_ARGS__), channel, bw::LogPriority::eWARNING, __func__, __FILE__, __LINE__); }
    #define BW_LOG_ERROR(channel, format, ...)   { bw::log::message(bw::internal::format_log_message(format, __VA_ARGS__), channel, bw::LogPriority::eERROR,   __func__, __FILE__, __LINE__); }
    #define BW_LOG_FATAL(channel, format, ...)   { bw::log::message(bw::internal::format_log_message(format, __VA_ARGS__), channel, bw::LogPriority::eFATAL,   __func__, __FILE__, __LINE__); }
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