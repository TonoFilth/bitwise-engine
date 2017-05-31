////////////////////////////////////////////////////////////////////////////////
//  Template function definitions
////////////////////////////////////////////////////////////////////////////////
template <size_t Len, size_t Align, typename T>
template <typename ...Args>
PImpl<Len, Align, T>::PImpl(Args&& ...args) :
	m_valid(true)
{
	static_assert(sizeof(T)  <= Len,             "PImpl: Size needs to be changed");
	static_assert(Len        <= sizeof(T) * 1.1, "PImpl: Size is too big");
	static_assert(alignof(T) == Align,           "PImpl: Alignment needs to be changed");
	
    new (&m_impl) T(std::forward<Args>(args)...);
}

// -----------------------------------------------------------------------------

template <size_t Len, size_t Align, typename T>
PImpl<Len, Align, T>::~PImpl()
{
	T* impl = (T*) &m_impl;
	impl->~T();
}

// -----------------------------------------------------------------------------

template <size_t Len, size_t Align, typename T>
PImpl<Len, Align, T>::PImpl(const PImpl<Len, Align, T>& toCopy) :
	m_valid(true)
{
	new (&m_impl) T(toCopy);
}

// -----------------------------------------------------------------------------

template <size_t Len, size_t Align, typename T>
PImpl<Len, Align, T>& PImpl<Len, Align, T>::operator=(const PImpl<Len, Align, T>& toCopy)
{
	if (this != &toCopy)
	{
		// Destroy current implementation
		T* impl = (T*) &m_impl;
		impl->~T();

		new (&m_impl) T(toCopy);
	}

	return *this;
}

// -----------------------------------------------------------------------------

//template <size_t Len, size_t Align, typename T>
//PImpl<Len, Align, T>::PImpl(PImpl<Len, Align, T>&& toMove)
//{
//	m_impl = std::move(toMove.m_impl);
//	toMove.m_valid = false;
//}
//
//// -----------------------------------------------------------------------------
//
//template <size_t Len, size_t Align, typename T>
//PImpl<Len, Align, T>& PImpl<Len, Align, T>::operator=(PImpl<Len, Align, T>&& toMove)
//{
//	if (this != &toMove)
//	{
//		// Destroy current implementation
//		T* impl = (T*) &m_impl;
//		impl->~T();
//
//		// Move the implementation data
//		m_impl = std::move(toMove.m_impl);
//
//		toMove.m_valid = true;
//	}
//
//	return *this;
//}

// -----------------------------------------------------------------------------

template <size_t Len, size_t Align, typename T>
PImpl<Len, Align, T>::operator T*()
{
	return (T*) &m_impl;
}

// -----------------------------------------------------------------------------

template <size_t Len, size_t Align, typename T>
PImpl<Len, Align, T>::operator const T*() const
{
	return (const T*) &m_impl;
}

// -----------------------------------------------------------------------------

template <size_t Len, size_t Align, typename T>
PImpl<Len, Align, T>::operator T&()
{
	return (T&) m_impl;
}

// -----------------------------------------------------------------------------

template <size_t Len, size_t Align, typename T>
PImpl<Len, Align, T>::operator const T&() const
{
	return (const T&) m_impl;
}