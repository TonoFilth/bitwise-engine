#ifndef BW_BASE_THREAD_H
#define BW_BASE_THREAD_H

#include "Bw/Base/Common/Module.h"
#include "Bw/Base/Multithreading/ModuleTypes.h"
#include "Bw/Base/_detail/MultithreadingInternal.h"

namespace bw
{
namespace thread
{
	BW_BASE_API void destroy(Thread* thread);

	void run(Thread* thread);

	Thread* create(ThreadEntryPoint& entryPoint);

	template <class F>
	Thread* create(F functor, void* data)
	{
		ThreadEntryPoint* entryPoint = internal::multithreading_allocator().allocateObject<ThreadEntryPointFunctor<F>>(functor, data);
		return thread::create(*entryPoint);
	}

	template <class T>
	Thread* create(void (T::*function)(void*), void* data, T* object)
	{
		ThreadEntryPoint* entryPoint = internal::multithreading_allocator().allocateObject<ThreadEntryPointMember<T>>(function, data, object);
		return thread::create(*entryPoint);
	}

}	// namespace thread
}	// namespace bw

#endif BW_BASE_THREAD_H