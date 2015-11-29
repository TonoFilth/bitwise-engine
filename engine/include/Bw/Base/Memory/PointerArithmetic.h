#ifndef BW_BASE_POINTER_ARITHMETIC_H
#define BW_BASE_POINTER_ARITHMETIC_H

#include "Bw/Base/Common/Module.h"

namespace bw
{
namespace memory
{

////////////////////////////////////////////////////////////////////////////////
//  Pointer arithmetic functions
////////////////////////////////////////////////////////////////////////////////
BW_INLINE BW_BASE_API void* align_forward(void* ptr, size_t alignment);
BW_INLINE BW_BASE_API void* align_forward(void* ptr, size_t alignment, u8_t& usedAlignmentBytes);
BW_INLINE BW_BASE_API void* pointer_add(void* ptr, size_t bytes);
BW_INLINE BW_BASE_API void* pointer_sub(void* ptr, size_t bytes);
BW_INLINE BW_BASE_API const void* pointer_add(const void* ptr, size_t bytes);
BW_INLINE BW_BASE_API const void* pointer_sub(const void* ptr, size_t bytes);

// Function definitions
#include "Bw/Base/_detail/PointerArithmetic.inl"

}   // namespace memory
}   // namespace bw

#endif  // BW_BASE_POINTER_ARITHMETIC_H