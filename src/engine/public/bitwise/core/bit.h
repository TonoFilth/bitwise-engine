#include <type_traits>

#include "bitwise/core/assert.h"
#include "bitwise/core/macros.h"
#include "bitwise/core/export.h"
#include "bitwise/core/basic_types.h"

namespace bw
{
namespace bit
{
    template<typename T, typename = std::enable_if_t<std::is_integral<T>::value>>
    BW_FORCE_INLINE T mask(T bit);

    template <typename T, typename = std::enable_if_t<std::is_integral<T>::value>>
    BW_FORCE_INLINE T set(T bits, uint8_t bit);

    template <typename T, typename = std::enable_if_t<std::is_integral<T>::value>>
    BW_FORCE_INLINE T unset(T bits, uint8_t bit);

    template <typename T, typename = std::enable_if_t<std::is_integral<T>::value>>
    BW_FORCE_INLINE T toggle(T bits, uint8_t bit);

    template <typename T, typename = std::enable_if_t<std::is_integral<T>::value>>
    BW_FORCE_INLINE T complement(T bits);

    template <typename T, typename = std::enable_if_t<std::is_integral<T>::value>>
    BW_FORCE_INLINE bool is_set(T bits, uint8_t bit);

    template <typename T, typename = std::enable_if_t<std::is_integral<T>::value>>
    BW_FORCE_INLINE const char* to_string(T bits);

    template <typename T, typename = std::enable_if_t<std::is_integral<T>::value>>
    BW_FORCE_INLINE const char* to_string(char* buffer, size_t bufferSize, T bits);

}   // namespace bit
}   // namespace bw

#include "bitwise/core/bit.inl"