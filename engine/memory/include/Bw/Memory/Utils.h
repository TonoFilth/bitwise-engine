#ifndef BW_MEMORY_UTILS_H
#define BW_MEMORY_UTILS_H

#include "Bw/Base/Types.h"
#include "Bw/Memory/Export.h"

namespace bw
{
namespace MemoryUtils
{

////////////////////////////////////////////////////////////////////////////////
//  Public functions
////////////////////////////////////////////////////////////////////////////////
BW_MEMORY_API void PrintRange(const void* start, size_t offsetEnd);
BW_MEMORY_API void PrintRange(const void* start, const void* end);

}	// namespace MemoryUtils
}	// namespace bw

#endif	// BW_MEMORY_UTILS_H