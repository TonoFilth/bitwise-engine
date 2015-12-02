#ifndef BW_BASE_THREAD_LOCAL_H
#define BW_BASE_THREAD_LOCAL_H

#include "Bw/Base/Common/Module.h"
#include "Bw/Base/Multithreading/ModuleTypes.h"

namespace bw
{
namespace thread_local
{

////////////////////////////////////////////////////////////////////////////////
//  ThreadLocal
////////////////////////////////////////////////////////////////////////////////
BW_BASE_API ThreadLocalIndex create(void* value = nullptr);
BW_BASE_API void destroy(ThreadLocalIndex tls);

BW_BASE_API void  set_value(ThreadLocalIndex tls, void* value);
BW_BASE_API void* get_value(ThreadLocalIndex tls);

}	// namespace thread_local

////////////////////////////////////////////////////////////////////////////////
//  ThreadLocal
////////////////////////////////////////////////////////////////////////////////
template <class T>
class BW_BASE_API ThreadLocal
{
public:
	ThreadLocal(T* value = NULL);
	~ThreadLocal();

	ThreadLocal<T>& operator=(const ThreadLocal<T>& copyValue);
	ThreadLocal<T>& operator=(T* value);

	T& operator*()  const;
	T* operator->() const;
	operator T*()   const;

	bool isNull() const;

private:
	ThreadLocalIndex m_index;
};

// -----------------------------------------------------------------------------

template <class T>
ThreadLocal<T>::ThreadLocal(T* value) :
	m_index(thread_local::create(value))
{
}

// -----------------------------------------------------------------------------

template <class T>
ThreadLocal<T>::~ThreadLocal()
{
	thread_local::destroy(m_index);
}

// -----------------------------------------------------------------------------

template <class T>
ThreadLocal<T>& ThreadLocal<T>::operator=(const ThreadLocal<T>& copyValue)
{
	thread_local::set_value(m_index, thread_local::get_value(copyValue.m_index));
	return *this;
}

// -----------------------------------------------------------------------------

template <class T>
ThreadLocal<T>& ThreadLocal<T>::operator=(T* value)
{
	thread_local::set_value(m_index, value);
	return *this;
}

// -----------------------------------------------------------------------------

template <class T>
T& ThreadLocal<T>::operator*() const
{
	return *static_cast<T*>(thread_local::get_value(m_index));
}

// -----------------------------------------------------------------------------

template <class T>
T* ThreadLocal<T>::operator->() const
{
	return static_cast<T*>(thread_local::get_value(m_index));
}

// -----------------------------------------------------------------------------

template <class T>
ThreadLocal<T>::operator T*() const
{
	return static_cast<T*>(thread_local::get_value(m_index));
}

// -----------------------------------------------------------------------------

template <class T>
bool ThreadLocal<T>::isNull() const
{
	void* value = thread_local::get_value(m_index);

	return (value == NULL);
}

}	// namespace bw

#endif	// BW_BASE_THREAD_LOCAL_H