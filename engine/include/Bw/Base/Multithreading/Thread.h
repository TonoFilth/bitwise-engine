#ifndef BW_BASE_THREAD_H
#define BW_BASE_THREAD_H

#include "Bw/Base/Common/Module.h"
#include "Bw/Base/Multithreading/ModuleTypes.h"
#include "Bw/Base/Detail/MultithreadingInternal.h"

namespace bw
{
namespace thread
{
	template <class T> BW_BASE_API Thread* create(T functor, void* data);
	template <class T> BW_BASE_API Thread* create(void (T::*function)(void*), void* data, T* object);

	BW_BASE_API void destroy(Thread* thread);
	BW_BASE_API void run(Thread* thread);
	BW_BASE_API void wait(Thread* thread);
	BW_BASE_API void terminate(Thread* thread);

	BW_BASE_API uint64_t thread_id();
	BW_BASE_API uint64_t thread_id(Thread* thread);
	BW_BASE_API uint64_t main_thread_id();

	#include "Bw/Base/Detail/Thread.inl"

}	// namespace thread
}	// namespace bw

#endif BW_BASE_THREAD_H