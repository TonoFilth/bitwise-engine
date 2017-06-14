#pragma once

#include "bitwise/core/macros.h"
#include "bitwise/core/basic_types.h"

namespace bw
{
////////////////////////////////////////////////////////////////////////////////
/// \brief Brief description.
/// \todo Write brief description
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
        
        eUSER
    };
};

////////////////////////////////////////////////////////////////////////////////
/// \brief Brief description.
/// \todo Write brief description
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

////////////////////////////////////////////////////////////////////////////////
/// \brief Brief description.
/// \todo Write brief description
////////////////////////////////////////////////////////////////////////////////
namespace log
{
    const size_t kMaxChannels     = sizeof(uint32_t) * 8;               ///< TODO
    const size_t kMaxUserChannels = kMaxChannels - LogChannel::eUSER;   ///< TODO

	////////////////////////////////////////////////////////////////////////////
	/// \brief Brief description.
	/// \todo Write brief description.
	////////////////////////////////////////////////////////////////////////////
    BW_API void message(const char* function, const char* file, int line, const char* messageFormat, ...);

	////////////////////////////////////////////////////////////////////////////
	/// \brief Brief description.
	/// \todo Write brief description.
	////////////////////////////////////////////////////////////////////////////
    BW_API void message(uint8_t channel, int priority, const char* function, const char* file, int line, const char* messageFormat, ...);

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

////////////////////////////////////////////////////////////////////////////////
/// \namespace bw::log
/// \ingroup core
///
/// \details Detailed description.
/// \todo Write detailed description
////////////////////////////////////////////////////////////////////////////////