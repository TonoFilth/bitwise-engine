#ifndef BW_BASE_REAL_H
#define BW_BASE_REAL_H

#include "Bw/Base/Export.h"
#include "Bw/Base/Types.h"

namespace bw
{
namespace Real
{

////////////////////////////////////////////////////////////////////////////////
//	Constants
////////////////////////////////////////////////////////////////////////////////
#if defined(BW_DOUBLE_PRECISION)
	const real_t kMax = 1.7976931348623158e+308;
	const real_t kMin = 2.2250738585072014e-308;
#else
	const real_t kMax = 3.402823466e+38F;
	const real_t kMin = 1.175494351e-38F;
#endif

}	// namespace Real
}	// namespace bw

#endif	// BW_BASE_REAL_H