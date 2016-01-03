#ifndef BW_BASE_LIMITS_H
#define BW_BASE_LIMITS_H

#include "Bw/Base/Common/Export.h"
#include "Bw/Base/Common/Types.h"

namespace bw
{

////////////////////////////////////////////////////////////////////////////////
//	Integer limit constants
////////////////////////////////////////////////////////////////////////////////
#if BW_HAVE_LIMITS && BW_HAVE_CONSTEXPR

#include <climits>

#error "TODO"

#else

////////////////////////////////////////////////////////////////////////////////
// Signed integers
////////////////////////////////////////////////////////////////////////////////
const int8_t  BW_INT8_MAX  = 0x7F;
const int16_t BW_INT16_MAX = 0x7FFF;
const int32_t BW_INT32_MAX = 0x7FFFFFFF;
const int64_t BW_INT64_MAX = 0x7FFFFFFFFFFFFFFF;

// -----------------------------------------------------------------------------

const int8_t  BW_INT8_MIN  = (-BW_INT8_MAX  - 1);
const int16_t BW_INT16_MIN = (-BW_INT16_MAX - 1);
const int32_t BW_INT32_MIN = (-BW_INT32_MAX - 1);
const int64_t BW_INT64_MIN = (-BW_INT64_MAX - 1);

////////////////////////////////////////////////////////////////////////////////
// Unsigned integers
////////////////////////////////////////////////////////////////////////////////
const uint8_t  BW_UINT8_MAX  = 0xFF;
const uint16_t BW_UINT16_MAX = 0xFFFF;
const uint32_t BW_UINT32_MAX = 0xFFFFFFFF;
const uint64_t BW_UINT64_MAX = 0xFFFFFFFFFFFFFFFF;

////////////////////////////////////////////////////////////////////////////////
// Pointer types
////////////////////////////////////////////////////////////////////////////////
#if defined(BW_32BIT)

	const intptr_t  BW_INTPTR_MAX  = BW_INT32_MAX;
	const intptr_t  BW_INTPTR_MIN  = BW_INT32_MIN;
	const uintptr_t BW_UINTPTR_MAX = BW_UINT32_MAX;

#else

	const intptr_t  BW_INTPTR_MAX  = BW_INT64_MAX;
	const intptr_t  BW_INTPTR_MIN  = BW_INT64_MIN;
	const uintptr_t BW_UINTPTR_MAX = BW_UINT64_MAX;

#endif

const ptrdiff_t BW_PTRDIFF_MAX = BW_INTPTR_MAX;
const ptrdiff_t BW_PTRDIFF_MIN = BW_INTPTR_MIN;
const size_t    BW_SIZE_MAX    = BW_UINTPTR_MAX;

////////////////////////////////////////////////////////////////////////////////
// Real numbers
////////////////////////////////////////////////////////////////////////////////
#if defined(BW_DOUBLE_PRECISION)
	const real_t BW_REAL_MAX = 1.7976931348623158e+308;
	const real_t BW_REAL_MIN = 2.2250738585072014e-308;
#else
	const real_t BW_REAL_MAX = 3.402823466e+38F;
	const real_t BW_REAL_MIN = 1.175494351e-38F;
#endif

#endif	// BW_HAVE_LIMITS && BW_HAVE_CONSTEXPR

}	// namespace bw

#endif	// BW_BASE_LIMITS_H