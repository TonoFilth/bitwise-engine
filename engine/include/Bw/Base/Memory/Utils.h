#ifndef BW_BASE_MEMORY_UTILS_H
#define BW_BASE_MEMORY_UTILS_H

#include "Bw/Base/Config.h"

namespace bw
{
namespace MemoryUtils
{

////////////////////////////////////////////////////////////////////////////////
//  Public functions
////////////////////////////////////////////////////////////////////////////////
BW_BASE_API void PrintRange(const void* start, size_t offsetEnd);
BW_BASE_API void PrintRange(const void* start, const void* end);

}	// namespace MemoryUtils
}	// namespace bw

#endif	// BW_BASE_MEMORY_UTILS_H