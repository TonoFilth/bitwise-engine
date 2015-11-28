#ifndef BW_BASE_INTEGER_H
#define BW_BASE_INTEGER_H

#include <type_traits>
#include "Bw/Base/Common/Module.h"

namespace bw
{
namespace integer
{

////////////////////////////////////////////////////////////////////////////////
//	Public functions
////////////////////////////////////////////////////////////////////////////////
template <class T, typename = std::enable_if<std::is_integral<T>::value>::type>
BW_BASE_API BW_INLINE bool is_power_of_2(T x)
{
	return (x > 0 && !(x & (x-1)));
}

// -----------------------------------------------------------------------------

template <class T, typename = std::enable_if<std::is_integral<T>::value>::type>
BW_BASE_API BW_INLINE bool is_multiple_of(T a, T b)
{
	return (a % b == 0);
}

}	// namespace integer
}	// namespace bw

#endif	// BW_BASE_INTEGER_H