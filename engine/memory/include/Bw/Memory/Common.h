#ifndef BW_MEMORY_COMMON_H
#define BW_MEMORY_COMMON_H

#include "Bw/Base/Types.h"
#include "Bw/Memory/Export.h"
#include "Bw/Memory/Types.h"

////////////////////////////////////////////////////////////////////////////////
//  Macros
////////////////////////////////////////////////////////////////////////////////
#define BW_NEW(T, ...) bw::Memory::GlobalAllocator().allocateObject<T>(__VA_ARGS__)
#define BW_DELETE(ptr) bw::Memory::GlobalAllocator().deallocateObject(ptr); ptr = nullptr

namespace bw
{
namespace Memory
{

////////////////////////////////////////////////////////////////////////////////
//  Global allocators
////////////////////////////////////////////////////////////////////////////////
BW_MEMORY_API Allocator& SystemAllocator();		// Raw memory allocation
BW_MEMORY_API Allocator& GlobalAllocator();		// Global heap allocator
BW_MEMORY_API Allocator& DebugAllocator();		// Debug memory allocator

////////////////////////////////////////////////////////////////////////////////
//  Pointer arithmetic functions
////////////////////////////////////////////////////////////////////////////////
BW_INLINE BW_MEMORY_API void* AlignForward(void* ptr, size_t alignment);
BW_INLINE BW_MEMORY_API void* AlignForward(void* ptr, size_t alignment, uint8_t& usedAlignmentBytes);

BW_INLINE BW_MEMORY_API void* PointerAdd(void* ptr, size_t bytes);
BW_INLINE BW_MEMORY_API void* PointerSub(void* ptr, size_t bytes);

BW_INLINE BW_MEMORY_API const void* PointerAdd(const void* ptr, size_t bytes);
BW_INLINE BW_MEMORY_API const void* PointerSub(const void* ptr, size_t bytes);

BW_INLINE BW_MEMORY_API bool IsAligned(const void* addr, size_t alignment);

}   // namespace Memory
}   // namespace bw

////////////////////////////////////////////////////////////////////////////////
//  Function definitions
////////////////////////////////////////////////////////////////////////////////
#include "Bw/Memory/Common.inl"

#endif  // BW_MEMORY_COMMON_H