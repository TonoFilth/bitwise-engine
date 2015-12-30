////////////////////////////////////////////////////////////////////////////////
//  Inline function definitions
////////////////////////////////////////////////////////////////////////////////
template <unsigned N>
ScopeAllocator<N>::ScopeAllocator() : m_size(0), m_capacity(N), m_top(m_memory)
{
}

// -----------------------------------------------------------------------------

template <unsigned N>
void* ScopeAllocator<N>::allocate(size_t size, size_t alignment)
{
	size_t totalSize = size + alignment;

	// Buffer exhausted
	BW_ASSERT(m_size + totalSize < m_capacity);

	void* data = memory::align_forward(m_top, alignment);
	m_top   = memory::pointer_add(m_top, totalSize);
	m_size += totalSize;

	return data;
}

// -----------------------------------------------------------------------------

template <unsigned N>
void ScopeAllocator<N>::deallocate(void* data)
{
}

// -----------------------------------------------------------------------------

template <unsigned N>
size_t ScopeAllocator<N>::allocatedSize() const
{
	return m_size;
}

// -----------------------------------------------------------------------------

template <unsigned N>
size_t ScopeAllocator<N>::allocatedSize(void* data) const
{
	return Allocator::kSizeNotTracked;
}