#ifndef BW_BASE_POINTER_H
#define BW_BASE_POINTER_H

#include "Bw/Base/Types.h"
#include "Bw/Base/Integer.h"

namespace bw
{
namespace Pointer
{

////////////////////////////////////////////////////////////////////////////////
//	Constants
////////////////////////////////////////////////////////////////////////////////
#if defined(BW_32BIT)

	const intptr_t  kIntPtrMax  = bw::Integer::kInt32Max;
	const intptr_t  kIntPtrMin  = bw::Integer::kInt32Min;
	const uintptr_t kUintPtrMax = bw::Integer::kUint32Max;

#else

	const intptr_t  kIntPtrMax  = bw::Integer::kInt64Max;
	const intptr_t  kIntPtrMin  = bw::Integer::kInt64Min;
	const uintptr_t kUintPtrMax = bw::Integer::kUint64Max;

#endif

const ptrdiff_t kPtrDiffMax = bw::Pointer::kIntPtrMax;
const ptrdiff_t kPtrDiffMin = bw::Pointer::kIntPtrMin;

////////////////////////////////////////////////////////////////////////////////
//	Public functions
////////////////////////////////////////////////////////////////////////////////
BW_INLINE BW_BASE_API void* AlignForward(void* ptr, size_t alignment);
BW_INLINE BW_BASE_API void* AlignForward(void* ptr, size_t alignment, uint8_t& usedAlignmentBytes);

BW_INLINE BW_BASE_API void* Add(void* ptr, size_t bytes);
BW_INLINE BW_BASE_API void* Sub(void* ptr, size_t bytes);

BW_INLINE BW_BASE_API const void* Add(const void* ptr, size_t bytes);
BW_INLINE BW_BASE_API const void* Sub(const void* ptr, size_t bytes);

BW_BASE_API BW_INLINE bool IsAligned(const void* ptr, size_t alignment);

}	// namespace Pointer
}	// namespace bw

#include "Bw/Base/Pointer.inl"

#endif	// BW_BASE_POINTER_H