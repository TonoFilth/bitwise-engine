////////////////////////////////////////////////////////////////////////////////
//  Inline function definitions
////////////////////////////////////////////////////////////////////////////////
template <class T>
PoolAllocator<T>::PoolAllocator(size_t poolSize) :
	m_pool(nullptr),
	m_free(nullptr),
	m_poolSize(poolSize),
	m_used(0)
{
	static_assert(sizeof(T) >= sizeof(PoolAllocator::offset_t), "PoolAllocator: Object size doesn't fit the minimum required");

	// Check poolSize range: [1, PoolAllocator::OFFSET_MAX]
	BW_ASSERT(poolSize > 0);
	BW_ASSERT(poolSize <= PoolAllocator::OFFSET_MAX);
}

// -----------------------------------------------------------------------------

template <class T>
PoolAllocator<T>::~PoolAllocator()
{
	if (m_pool)
	{
		// Some objects weren't returned to the pool
		BW_ASSERT(m_used == 0);

		memory::page_allocator().deallocate(m_pool);

		m_pool     = nullptr;
		m_free     = nullptr;
		m_used     = 0;
		m_poolSize = 0;
	}
};

// -----------------------------------------------------------------------------

template <class T>
void* PoolAllocator<T>::allocate(size_t size, size_t alignment)
{
	BW_ASSERT(size == sizeof(T) && alignment == alignof(T));
	BW_ASSERT(m_used < m_poolSize);

	// Because we don't allocate memory when this class
	// is constructed we must check if the pool has been created or not
	if (!m_pool)
		createPool();

	void* data = m_free;

	PoolAllocator::FreeNode* freeNode = (PoolAllocator::FreeNode*) m_free;
	m_free  = memory::pointer_add(m_pool, freeNode->_next * sizeof(T));
	m_used += 1;

	return data;
}

// -----------------------------------------------------------------------------

template <class T>
void PoolAllocator<T>::deallocate(void* data)
{
	BW_ASSERT(memory::is_aligned(data, alignof(T)));

	PoolAllocator::FreeNode* collected = (PoolAllocator::FreeNode*) data;

	uintptr_t diff   = uintptr_t(m_free) - uintptr_t(m_pool);
	uintptr_t offset = diff / sizeof(T);

	collected->_next = static_cast<PoolAllocator::offset_t>(offset);
	m_free  = collected;
	m_used -= 1;
}

// -----------------------------------------------------------------------------

template <class T>
template <class ...Args>
T* PoolAllocator<T>::next(Args&& ...args)
{
	void* data = allocate(sizeof(T), alignof(T));

	return new (data) T(std::forward<Args>(args)...);
}

// -----------------------------------------------------------------------------

template <class T>
void PoolAllocator<T>::collect(T* obj)
{
	if (obj)
	{
		obj->~T();
		deallocate(obj);
	}
}

// -----------------------------------------------------------------------------

template <class T>
size_t PoolAllocator<T>::allocatedSize() const
{
	return m_poolSize * sizeof(T);
}

// -----------------------------------------------------------------------------

template <class T>
size_t PoolAllocator<T>::allocatedSize(void* data) const
{
	return sizeof(T);
}

// -----------------------------------------------------------------------------

template <class T>
void PoolAllocator<T>::createPool()
{
	BW_ASSERT(m_used == 0);

	auto& allocator = memory::page_allocator();

	m_pool = allocator.allocate(m_poolSize * sizeof(T), alignof(T));
	m_free = m_pool;

	BW_ASSERT(memory::is_aligned(m_pool, alignof(T)));

	PoolAllocator::offset_t i = 0;

	while (i < m_poolSize)
	{
		PoolAllocator::FreeNode* freeNode = (PoolAllocator::FreeNode*) memory::pointer_add(m_pool, i * sizeof(T));
		freeNode->_next = ++i;
	}
}