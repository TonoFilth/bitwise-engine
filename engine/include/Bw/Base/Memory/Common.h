#ifndef BW_BASE_MEMORY_COMMON_H
#define BW_BASE_MEMORY_COMMON_H

#include "Bw/Base/Config.h"
#include "Bw/Base/Memory/Types.h"

namespace bw
{
namespace Memory
{

////////////////////////////////////////////////////////////////////////////////
//  Global allocators
////////////////////////////////////////////////////////////////////////////////
BW_BASE_API Allocator& GlobalAllocator();
BW_BASE_API Allocator& SystemAllocator();
BW_BASE_API Allocator& DebugAllocator();

////////////////////////////////////////////////////////////////////////////////
//  Pointer arithmetic functions
////////////////////////////////////////////////////////////////////////////////
BW_INLINE BW_BASE_API void* AlignForward(void* ptr, size_t alignment);
BW_INLINE BW_BASE_API void* AlignForward(void* ptr, size_t alignment, uint8_t& usedAlignmentBytes);

BW_INLINE BW_BASE_API void* PointerAdd(void* ptr, size_t bytes);
BW_INLINE BW_BASE_API void* PointerSub(void* ptr, size_t bytes);

BW_INLINE BW_BASE_API const void* PointerAdd(const void* ptr, size_t bytes);
BW_INLINE BW_BASE_API const void* PointerSub(const void* ptr, size_t bytes);

BW_BASE_API BW_INLINE bool IsAligned(const void* addr, size_t alignment);

}   // namespace Memory
}   // namespace bw

////////////////////////////////////////////////////////////////////////////////
//  Function definitions
////////////////////////////////////////////////////////////////////////////////
#include "Bw/Base/Detail/MemoryCommon.inl"

#endif  // BW_BASE_MEMORY_COMMON_H