////////////////////////////////////////////////////////////////////////////////
//  Template function definitions
////////////////////////////////////////////////////////////////////////////////
template <size_t Len, size_t Align>
PImpl<Len, Align>::PImpl() :
	m_initialized(false)
{
}

// -----------------------------------------------------------------------------

template <size_t Len, size_t Align>
PImpl<Len, Align>::~PImpl()
{
	// Forgot to call PImpl::destroy()
	BW_ASSERT(!m_initialized);
}

// -----------------------------------------------------------------------------

template <size_t Len, size_t Align>
template <class T, class ...Args>
T* PImpl<Len, Align>::create(Args&& ...args)
{
	static_assert(sizeof(T)  <= Len,             "PImpl: Size needs to be changed");
	static_assert(Len        <= sizeof(T) * 1.1, "PImpl: Size is too big");
	static_assert(alignof(T) == Align,           "PImpl: Alignment needs to be changed");

	m_initialized = true;
    return new (&m_impl) T(std::forward<Args>(args)...);
}

// -----------------------------------------------------------------------------

template <size_t Len, size_t Align>
template <class T>
T* PImpl<Len, Align>::copy(const PImpl<Len, Align>& src)
{
	if (src.m_initialized)
		return create<T>((const T&) src.m_impl);	// Call the copy ctor
	else
		return nullptr;
}

// -----------------------------------------------------------------------------

template <size_t Len, size_t Align>
template <class T>
void PImpl<Len, Align>::destroy()
{
	T* impl = (T*) &m_impl;
	impl->~T();
	m_initialized = false;
}

// -----------------------------------------------------------------------------

template <size_t Len, size_t Align>
template <class T>
PImpl<Len, Align>::operator T*()
{
	return (m_initialized ? (T*) &m_impl : nullptr);
}

// -----------------------------------------------------------------------------

template <size_t Len, size_t Align>
template <class T>
PImpl<Len, Align>::operator T*() const
{
	return (m_initialized ? (const T*) &m_impl : nullptr);
}

// -----------------------------------------------------------------------------

template <size_t Len, size_t Align>
template <class T>
PImpl<Len, Align>::operator T&()
{
	BW_ASSERT(m_initialized);
	return (T&) m_impl;
}

// -----------------------------------------------------------------------------

template <size_t Len, size_t Align>
template <class T>
PImpl<Len, Align>::operator T&() const
{
	BW_ASSERT(m_initialized);
	return (const T&) m_impl;
}

// -----------------------------------------------------------------------------

template <size_t Len, size_t Align>
bool PImpl<Len, Align>::isValid() const
{
	return m_initialized;
}