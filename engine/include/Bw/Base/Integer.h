#ifndef BW_BASE_INTEGER_H
#define BW_BASE_INTEGER_H

#include <type_traits>
#include "Bw/Base/Common/Export.h"

namespace bw
{

////////////////////////////////////////////////////////////////////////////////
//	Public functions
////////////////////////////////////////////////////////////////////////////////
template <class T, typename = std::enable_if<std::is_integral<T>::value>::type>
BW_INLINE bool IsPowerOf2(T x)
{
	return (x > 0 && !(x & (x-1)));
}

// -----------------------------------------------------------------------------

template <class T, typename = std::enable_if<std::is_integral<T>::value>::type>
BW_INLINE bool IsMultipleOf(T a, T b)
{
	return (a % b == 0);
}

}	// namespace bw

#endif	// BW_BASE_INTEGER_H