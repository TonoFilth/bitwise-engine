#ifndef BW_BASE_FEATURES_H
#define BW_BASE_FEATURES_H

#include "Bw/Base/Common/Macros.h"

namespace bw
{

////////////////////////////////////////////////////////////////////////////////
//	Implementation features
////////////////////////////////////////////////////////////////////////////////
#if defined(BW_SYSTEM_WINDOWS)
#   define BW_HAVE_STDINT    1
#	define BW_HAVE_CONSTEXPR 0
#	define BW_HAVE_LIMITS    1
#else
#	define BW_HAVE_LIMITS 1
#endif

}	// namespace bw

#endif	// BW_BASE_FEATURES_H