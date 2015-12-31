#ifndef BW_BASE_MULTITHREADING_INTERNAL_H
#define BW_BASE_MULTITHREADING_INTERNAL_H

#include "Bw/Base/Common.h"
#include "Bw/Base/Config.h"
#include "Bw/Base/Memory/Common.h"
#include "Bw/Base/Multithreading/Types.h"

namespace bw
{
namespace internal
{

////////////////////////////////////////////////////////////////////////////////
//	Private types
////////////////////////////////////////////////////////////////////////////////
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

////////////////////////////////////////////////////////////////////////////////
//	Public functions
////////////////////////////////////////////////////////////////////////////////
BW_BASE_API Thread* create_thread(ThreadEntryPoint& entryPoint);
BW_BASE_API void    set_main_thread_id(uint64_t id);
BW_INLINE BW_BASE_API Allocator& multithreading_allocator() { return Memory::SystemAllocator(); }

BW_BASE_API void init_mutex_pool();
BW_BASE_API void init_thread_pool();

BW_BASE_API void destroy_mutex_pool();
BW_BASE_API void destroy_thread_pool();

}	// namespace internal
}	// namespace bw

#endif	// BW_BASE_MULTITHREADING_INTERNAL_H