#if !defined(BW_DOXYPRESS)
#pragma once

#include "bitwise/core/macros.h"

namespace bw
{
namespace internal
{
namespace network
{
	#if defined(BW_PLATFORM_WINDOWS)
	const size_t kTcpServerSize = 256;
	#endif
}	// namespace network
}	// namespace internal
}	// namespace bw
#endif