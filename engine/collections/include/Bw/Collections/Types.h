#ifndef BW_COLLECTIONS_TYPES_H
#define BW_COLLECTIONS_TYPES_H

#include <cstdlib>
#include "Bw/Base/Macros.h"
#include "Bw/Memory/Types.h"
#include "Bw/Collections/Export.h"

namespace bw
{

////////////////////////////////////////////////////////////////////////////////
//  Array
////////////////////////////////////////////////////////////////////////////////
template <typename T>
struct Array
{
	Array(Allocator& allocator);
	Array(const Array& other);
	Array& operator=(const Array& other);
	~Array();

	const T& operator[](const int index) const;
	      T& operator[](const int index);

	size_t     _size;
	size_t     _capacity;
	Allocator& _allocator;
	T*         _data;
};

}	// namespace bw

#endif	// BW_COLLECTIONS_TYPES_H