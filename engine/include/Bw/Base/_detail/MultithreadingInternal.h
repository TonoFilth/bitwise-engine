#ifndef BW_BASE_MULTITHREADING_INTERNAL_H
#define BW_BASE_MULTITHREADING_INTERNAL_H

#include "Bw/Base/Common/Module.h"
#include "Bw/Base/Memory/ModuleTypes.h"

namespace bw
{
struct ThreadEntryPoint
{
	ThreadEntryPoint() : data(nullptr) {}
	explicit ThreadEntryPoint(void* d) : data(d) {}

	virtual ~ThreadEntryPoint() = default;
	virtual void run(void* data) = 0;

	void* data;
};

// -----------------------------------------------------------------------------

template <class F>
struct ThreadEntryPointFunctor : public ThreadEntryPoint
{
	ThreadEntryPointFunctor(F f, void* data) : ThreadEntryPoint(data), functor(f) {}
	virtual ~ThreadEntryPointFunctor() = default;

	void run(void* data) override
	{
		functor(data);
	}

	F functor;
};

// -----------------------------------------------------------------------------

template <class T>
struct ThreadEntryPointMember : public ThreadEntryPoint
{
	ThreadEntryPointMember(void (T::*f) (void*), void* data, T* obj) :
			ThreadEntryPoint(data),
			object(obj),
			function(f)
	{
	}

	virtual ~ThreadEntryPointMember() = default;

	void run(void* data) override
	{
		(object->*function)(data);
	}

	T* object;
	void (T::*function) (void* data);
};

namespace internal
{

////////////////////////////////////////////////////////////////////////////////
//	Public functions
////////////////////////////////////////////////////////////////////////////////
BW_BASE_API Allocator& multithreading_allocator();

}	// namespace internal
}	// namespace bw

#endif	// BW_BASE_MULTITHREADING_INTERNAL_H