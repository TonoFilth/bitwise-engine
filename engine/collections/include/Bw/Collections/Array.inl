////////////////////////////////////////////////////////////////////////////////
//  Template definitions
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
//  Template definitions
////////////////////////////////////////////////////////////////////////////////
template <typename T>
BW_INLINE Array<T>::Array(Allocator& allocator) :
	_size(0),
	_capacity(0),
	_allocator(allocator),
	_data(nullptr)
{
}

// -----------------------------------------------------------------------------

template <typename T>
Array<T>::Array(const Array<T>& other) :
	_size(0),
	_capacity(0),
	_allocator(other._allocator),
	_data(nullptr)
{
	array::Copy(other, *this);
}

// -----------------------------------------------------------------------------

template <typename T>
Array<T>& Array<T>::operator=(const Array<T>& other)
{
	if (this == &other)
	{
		return *this;
	}

	array::Copy(other, *this);
}

// -----------------------------------------------------------------------------

template <typename T>
Array<T>::~Array()
{
	_allocator.deallocate(_data);
}

// -----------------------------------------------------------------------------

template <typename T>
BW_INLINE const T& Array<T>::operator[](const int index) const
{
	return *(_data + index);
}

// -----------------------------------------------------------------------------

template <typename T>
BW_INLINE T& Array<T>::operator[](const int index)
{
	return *(_data + index);
}

// -----------------------------------------------------------------------------

template <typename T>
BW_INLINE bool array::Any(const Array<T>& a)
{
	return a._size > 0;
}

// -----------------------------------------------------------------------------

template <typename T>
void array::Copy(const Array<T>& src, Array<T>& dst)
{
	size_t newSize = src._size;

	array::SetCapacity(dst, src._capacity);
	memcpy(dst._data, src._data, sizeof(T) * n);
	dst._size = newSize;
}

// -----------------------------------------------------------------------------

template <typename T>
bool array::Empty(const Array<T>& a)
{
	return a._size == 0;
}

// -----------------------------------------------------------------------------

template <typename T>
BW_INLINE void array::Trim(Array<T>& a)
{
	array::SetCapacity(a, a._size);
}

// -----------------------------------------------------------------------------

template <typename T>
void array::Grow(Array<T>& a, size_t minCapacity)
{
	size_t newCapacity = a._capacity * 2 + 8;

	if (newCapacity < minCapacity)
	{
		newCapacity = minCapacity;
	}

	SetCapacity(a, newCapacity);
}

// -----------------------------------------------------------------------------

template <typename T>
void array::PushBack(Array<T>& a, const T& item)
{
	if (a._size + 1 > a._capacity)
	{
		array::Grow(a);
	}

	a._data[a._size++] = item;
}

// -----------------------------------------------------------------------------

template <typename T>
BW_INLINE void array::PopBack(Array<T>& a)
{
	a._size--;
}

// -----------------------------------------------------------------------------

template <typename T>
void array::Resize(Array<T>& a, size_t newSize)
{
	if (newSize > a._capacity)
	{
		Grow(a, newSize);
	}

	a._size = newSize;
}

// -----------------------------------------------------------------------------

template <typename T>
void array::Reserve(Array<T>& a, size_t newCapacity)
{
	if (newCapacity > a._capacity)
	{
		array::SetCapacity(a, newCapacity);
	}
}

// -----------------------------------------------------------------------------

template <typename T>
void array::SetCapacity(Array<T>& a, size_t newCapacity)
{
	if (newCapacity == a._capacity)
	{
		return;
	}

	if (newCapacity < a._size)
	{
		Resize(a, newCapacity);
	}

	T* newData = nullptr;

	if (newCapacity > 0)
	{
		newData = (T*) a._allocator.allocate(sizeof(T) * newCapacity, alignof(T));
		memcpy(newData, a._data, sizeof(T) * a._size);
	}

	a._allocator.deallocate(a._data);

	a._data     = newData;
	a._capacity = newCapacity;
}

// -----------------------------------------------------------------------------

template <typename T>
BW_INLINE void array::Clear(Array<T>& a)
{
	array::Resize(a, 0);
}

// -----------------------------------------------------------------------------

template <typename T>
BW_INLINE size_t array::Size(const Array<T>& a)
{
	return a._size;
}

// -----------------------------------------------------------------------------

template <typename T>
BW_INLINE T& array::Front(Array<T>& a)
{
	return a[0];
}

// -----------------------------------------------------------------------------

template <typename T>
BW_INLINE T& array::Back(Array<T>& a)
{
	return a[a._size-1];
}

// -----------------------------------------------------------------------------

template <typename T>
BW_INLINE const T& array::Front(const Array<T>& a)
{
	return a[0];
}

// -----------------------------------------------------------------------------

template <typename T>
BW_INLINE const T& array::Back(const Array<T>& a)
{
	return a[a._size-1];
}

// -----------------------------------------------------------------------------

template <typename T>
BW_INLINE T* array::Begin(Array<T>& a)
{
	return a._data;
}

// -----------------------------------------------------------------------------

template <typename T>
BW_INLINE const T* array::Begin(const Array<T>& a)
{
	return a._data;
}

// -----------------------------------------------------------------------------

template <typename T>
BW_INLINE T* array::End(Array<T>& a)
{
	return a._data + a._size;
}

// -----------------------------------------------------------------------------

template <typename T>
BW_INLINE const T* array::End(const Array<T>& a)
{
	return a._data + a._size;
}
