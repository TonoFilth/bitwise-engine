#ifndef BW_BASE_MEMORY_UTILS_H
#define BW_BASE_MEMORY_UTILS_H

#include "Bw/Base/Common/Module.h"

namespace bw
{
namespace memory
{

BW_BASE_API void print_range(const void* start, size_t offsetEnd);
BW_BASE_API void print_range(const void* start, const void* end);
BW_BASE_API BW_INLINE bool is_aligned(const void* addr, size_t alignment)
{
	return ((UPTR(addr) & (alignment - 1)) == 0);

}

}	// namespace memory
}	// namespace bw

#endif	// BW_BASE_MEMORY_UTILS_H