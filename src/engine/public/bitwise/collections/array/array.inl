template <typename T>
bw::Array<T>::Array() :
    m_array(nullptr),
    m_capacity(0),
    m_count(0),
    m_allocator(bw::memory::generic_allocator())
{
}

// -----------------------------------------------------------------------------

template <typename T>
bw::Array<T>::Array(size_t itemCapacity) :
    m_array(nullptr),
    m_capacity(0),
    m_count(0),
    m_allocator(bw::memory::generic_allocator())
{
    reserve(itemCapacity);
}

// -----------------------------------------------------------------------------

template <typename T>
bw::Array<T>::Array(Allocator& allocator) :
    m_array(nullptr),
    m_capacity(0),
    m_count(0),
    m_allocator(allocator)
{
}

// -----------------------------------------------------------------------------

template <typename T>
bw::Array<T>::Array(Allocator& allocator, size_t itemCapacity) :
    m_array(nullptr),
    m_capacity(0),
    m_count(0),
    m_allocator(allocator)
{
    reserve(itemCapacity);
}

// -----------------------------------------------------------------------------

template <typename T>
bw::Array<T>::Array(const Array& other) :
    m_array(nullptr),
    m_capacity(0),
    m_count(other.m_count),
    m_allocator(other.m_allocator)
{
    reserve(other.m_capacity);
    
    for (size_t i = 0; i < other.m_count; ++i)
    {
        *(m_array + i) = T(*(other.m_array + i));
    }
}

// -----------------------------------------------------------------------------

template <typename T>
bw::Array<T>::Array(Array&& other) :
    m_array(other.m_array),
    m_capacity(other.m_capacity),
    m_count(other.m_count),
    m_allocator(other.m_allocator)
{
    other.m_array    = nullptr;
    other.m_capacity = 0;
    other.m_count    = 0;
}

// -----------------------------------------------------------------------------

template <typename T>
bw::Array<T>& bw::Array<T>::operator=(const Array& other)
{
    if (this != &other)
    {
        resize(other.m_count);
        
        for (size_t i = 0; i < other.m_count; ++i)
        {
            *(m_array + i) = T(*(other.m_array + i));
        }
    }
}

// -----------------------------------------------------------------------------

template <typename T>
bw::Array<T>::~Array()
{
    if (m_array != nullptr)
    {
        m_allocator.deallocate(m_array);
        m_array = nullptr;
    }
}

// -----------------------------------------------------------------------------

template <typename T>
T& bw::Array<T>::operator[](size_t index)
{
    BW_ASSERT(index < m_count, "Index out of range %zu", index);
    return *(m_array + index);
}

// -----------------------------------------------------------------------------

template <typename T>
const T& bw::Array<T>::operator[](size_t index) const
{
    BW_ASSERT(index < m_count, "Index out of range %zu", index);
    return *(m_array + index);
}

// -----------------------------------------------------------------------------

template <typename T>
void bw::Array<T>::add(const T& item)
{
    if (m_count == m_capacity)
    {
        reserve(m_capacity * 2);
    }
    
    *(m_array + m_count) = item;
    ++m_count;
}

// -----------------------------------------------------------------------------

template <typename T>
void bw::Array<T>::insert(size_t index, const T& item)
{
    BW_ASSERT(index < m_count, "Index out of range %zu", index);

    if (m_count == m_capacity)
    {
        reserve(m_capacity * 2);
    }

    rshift(index);
    *(m_array + index) = item;
    ++m_count;
}

// -----------------------------------------------------------------------------

template <typename T>
typename bw::Array<T>::Iterator bw::Array<T>::insert(Iterator it, const T& item)
{
    if (m_count == m_capacity)
    {
        reserve(m_capacity * 2);
    }

    rshift(it);
    *it = item;
    ++m_count;

    return it;
}

// -----------------------------------------------------------------------------

template <typename T>
void bw::Array<T>::remove(size_t index)
{
    BW_ASSERT(index < m_count, "Index out of range %zu", index);

    (m_array + index)->~T();

    lshift(index);
    --m_count;
}

// -----------------------------------------------------------------------------

template <typename T>
typename bw::Array<T>::Iterator bw::Array<T>::remove(Iterator it)
{
    it->~T();
    lshift(it);
    --m_count;

    return it;
}

// -----------------------------------------------------------------------------

template <typename T>
void bw::Array<T>::resize(size_t itemCount, const T value)
{
    if (itemCount < m_count)
    {
        for (size_t i = itemCount; i < m_count; ++i)
        {
            (m_array + i)->~T();
        }

        m_count = itemCount;
    }
    else if (itemCount > m_count)
    {
        if (itemCount > m_capacity)
        {
            reserve((itemCount < m_capacity ? m_capacity : itemCount) * 2);
        }

        for (size_t i = m_count; i < itemCount; ++i)
        {
            *(m_array + i) = value;
        }

        m_count = itemCount;
    }
}

// -----------------------------------------------------------------------------

template <typename T>
void bw::Array<T>::reserve(size_t itemCapacity)
{
    if (itemCapacity > m_capacity)
    {
        T* newArray = (T*) m_allocator.allocate(sizeof(T) * itemCapacity, nullptr, alignof(T));

        if (m_array != nullptr)
        {
            memcpy(newArray, m_array, sizeof(T) * m_capacity);
        }

        m_array    = newArray;
        m_capacity = itemCapacity;
    }
}

// -----------------------------------------------------------------------------

template <typename T>
size_t bw::Array<T>::capacity() const
{
    return m_capacity;
}

// -----------------------------------------------------------------------------

template <typename T>
size_t bw::Array<T>::count() const
{
    return m_count;
}

// -----------------------------------------------------------------------------

template <typename T>
bool bw::Array<T>::empty() const
{
    return m_count == 0;
}

// -----------------------------------------------------------------------------

template <typename T>
typename bw::Array<T>::Iterator bw::Array<T>::begin()
{
    return m_array;
}

// -----------------------------------------------------------------------------

template <typename T>
typename bw::Array<T>::ConstIterator bw::Array<T>::begin() const
{
    return m_array;
}

// -----------------------------------------------------------------------------

template <typename T>
typename bw::Array<T>::Iterator bw::Array<T>::rbegin()
{
    return m_array + m_count - 1;
}

// -----------------------------------------------------------------------------

template <typename T>
typename bw::Array<T>::ConstIterator bw::Array<T>::rbegin() const
{
    return m_array + m_count - 1;
}

// -----------------------------------------------------------------------------

template <typename T>
typename bw::Array<T>::Iterator bw::Array<T>::end()
{
    return m_array + m_count;
}

// -----------------------------------------------------------------------------

template <typename T>
typename bw::Array<T>::ConstIterator bw::Array<T>::end() const
{
    return m_array + m_count;
}

// -----------------------------------------------------------------------------

template <typename T>
typename bw::Array<T>::Iterator bw::Array<T>::rend()
{
    return m_array - 1;
}

// -----------------------------------------------------------------------------

template <typename T>
typename bw::Array<T>::ConstIterator bw::Array<T>::rend() const
{
    return m_array - 1;
}

// -----------------------------------------------------------------------------

template <typename T>
void bw::Array<T>::lshift(size_t index)
{
    T* item = m_array + index;
    T* end  = m_array + m_count - 1;
    
    while (item != end)
    {
        *item = *(item + 1);
        ++item;
    }
}

// -----------------------------------------------------------------------------

template <typename T>
void bw::Array<T>::lshift(Iterator it)
{
    T* item = it;
    T* end  = m_array + m_count - 1;
    
    while (item != end)
    {
        *item = *(item + 1);
        ++item;
    }
}

// -----------------------------------------------------------------------------

template <typename T>
void bw::Array<T>::rshift(size_t index)
{
    T* item = m_array + m_count;
    T* end  = m_array + index;
    
    while (item != end)
    {
        *item = *(item - 1);
        --item;
    }
}

// -----------------------------------------------------------------------------

template <typename T>
void bw::Array<T>::rshift(Iterator it)
{
    T* item = m_array + m_count;
    T* end  = it;
    
    while (item != end)
    {
        *item = *(item - 1);
        --item;
    }
}