#ifndef BW_BASE_PIMPL_H
#define BW_BASE_PIMPL_H

#include <new>
#include <type_traits>
#include "Bw/Base/Assert.h"

namespace bw
{

////////////////////////////////////////////////////////////////////////////////
//	PImpl
////////////////////////////////////////////////////////////////////////////////
template <size_t Len, size_t Align>
class PImpl
{
public:
	PImpl();
	~PImpl();

	// Copy and assignment operator not implemented
	PImpl(const PImpl& toCopy)            = delete;
	PImpl& operator=(const PImpl& toCopy) = delete;

	// Move and assignment move not implemented
	PImpl(PImpl&& toMove)                 = delete;
	PImpl& operator=(PImpl&& toMove)      = delete;

public:
	template <class T, class ...Args>
	T* create(Args&& ...args);

	template <class T>
	T* copy(const PImpl<Len, Align>& src);

	template <class T>
	void destroy();

	// Implicit casts
	template <class T> operator T*();
	template <class T> operator T&();

	template <class T> operator T*() const;
	template <class T> operator T&() const;

	bool isValid() const;

private:
	typename std::aligned_storage<Len, Align>::type m_impl;
	bool m_initialized;
};

#include "Bw/Base/PImpl.inl"

}	// namespace bw

#endif	// BW_BASE_PIMPL_H