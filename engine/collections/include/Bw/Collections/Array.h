#ifndef BW_COLLECTIONS_ARRAY_H
#define BW_COLLECTIONS_ARRAY_H

#include "Bw/Collections/Types.h"

namespace bw
{

////////////////////////////////////////////////////////////////////////////////
//  array
////////////////////////////////////////////////////////////////////////////////
namespace array
{
	template <typename T> bool Any(const Array<T>& a);
	template <typename T> bool Empty(const Array<T>& a);

	template <typename T>       T& Front(Array<T>& a);
	template <typename T>       T& Back (Array<T>& a);
	template <typename T> const T& Front(const Array<T>& a);
	template <typename T> const T& Back (const Array<T>& a);

	template <typename T>       T* Begin(Array<T>& a);
	template <typename T>       T* End  (Array<T>& a);
	template <typename T> const T* Begin(const Array<T>& a);
	template <typename T> const T* End  (const Array<T>& a);

	template <typename T> void PushBack(Array<T>& a, const T& item);
	template <typename T> void PopBack(Array<T>& a);

	template <typename T> void Copy(const Array<T>& src, Array<T>& dst);
	template <typename T> void Clear(Array<T>& a);
	template <typename T> void Grow(Array<T>& a, size_t minCapacity = 0);
	template <typename T> void Trim(Array<T>& a);
	template <typename T> void Resize(Array<T>& a, size_t newSize);
	template <typename T> void Reserve(Array<T>& a, size_t newCapacity);
	template <typename T> void SetCapacity(Array<T>& a, size_t newCapacity);

	template <typename T> size_t Size(const Array<T>& a);
	
}	// namespace array

#include "Bw/Collections/Array.inl"

}	// namespace bw

#endif	// BW_COLLECTIONS_ARRAY_H