#ifndef BW_BASE_PIMPL_H
#define BW_BASE_PIMPL_H

#include <new>				// Placement new
#include <type_traits>		// static_assert
#include <utility>			// std::forward

namespace bw
{

////////////////////////////////////////////////////////////////////////////////
//	PImpl
////////////////////////////////////////////////////////////////////////////////
template <size_t Len, size_t Align, typename T>
class PImpl
{
public:
	template <typename ...Args>
	PImpl(Args&& ...args);
	~PImpl();

	PImpl(const PImpl& toCopy);
	PImpl& operator=(const PImpl& toCopy);

	// Move constructor and move assignment operator not implemented
	/*PImpl(PImpl&& toMove);
	PImpl& operator=(PImpl&& toMove);*/

public:
	// Implicit casts
	operator T*();
	operator T&();

	operator const T*() const;
	operator const T&() const;

private:
	typename std::aligned_storage<Len, Align>::type m_impl;
	bool m_valid;
};

#include "Bw/Base/PImpl.inl"

}	// namespace bw

#endif	// BW_BASE_PIMPL_H