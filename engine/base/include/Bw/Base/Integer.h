#ifndef BW_BASE_INTEGER_H
#define BW_BASE_INTEGER_H

#include <type_traits>
#include "Bw/Base/Export.h"

namespace bw
{
namespace Integer
{

////////////////////////////////////////////////////////////////////////////////
// Signed integers
////////////////////////////////////////////////////////////////////////////////
const int8_t  kInt8Max  = 0x7F;
const int16_t kInt16Max = 0x7FFF;
const int32_t kInt32Max = 0x7FFFFFFF;
const int64_t kInt64Max = 0x7FFFFFFFFFFFFFFF;

// -----------------------------------------------------------------------------

const int8_t  kInt8Min  = (-bw::Integer::kInt8Max  - 1);
const int16_t kInt16Min = (-bw::Integer::kInt16Max - 1);
const int32_t kInt32Min = (-bw::Integer::kInt32Max - 1);
const int64_t kInt64Min = (-bw::Integer::kInt64Max - 1);

////////////////////////////////////////////////////////////////////////////////
// Unsigned integers
////////////////////////////////////////////////////////////////////////////////
const uint8_t  kUint8Max  = 0xFF;
const uint16_t kUint16Max = 0xFFFF;
const uint32_t kUint32Max = 0xFFFFFFFF;
const uint64_t kUint64Max = 0xFFFFFFFFFFFFFFFF;

#if defined(BW_32BIT)
	const size_t kSizeMax = bw::Integer::kUint32Max;
#else
	const size_t kSizeMax = bw::Integer::kUint64Max;
#endif

////////////////////////////////////////////////////////////////////////////////
//	Public functions
////////////////////////////////////////////////////////////////////////////////
template <class T, typename std::enable_if<std::is_integral<T>::value>::type>
BW_INLINE bool IsPowerOf2(T x)
{
	return (x > 0 && !(x & (x-1)));
}

// -----------------------------------------------------------------------------

template <class T, typename std::enable_if<std::is_integral<T>::value>::type>
BW_INLINE bool IsMultipleOf(T a, T b)
{
	return (a % b == 0);
}

}	// namespace Integer
}	// namespace bw

#endif	// BW_BASE_INTEGER_H