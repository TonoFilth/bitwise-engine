#ifndef BW_BASE_THREAD_H
#define BW_BASE_THREAD_H

#include "Bw/Base/Common/Module.h"
#include "Bw/Base/Multithreading/ModuleTypes.h"
#include "Bw/Base/_detail/MultithreadingInternal.h"

namespace bw
{
namespace thread
{
	template <class T> BW_BASE_API Thread* create(T functor, void* data);
	template <class T> BW_BASE_API Thread* create(void (T::*function)(void*), void* data, T* object);

	BW_BASE_API void destroy(Thread* thread);

	void run(Thread* thread);

	#include "Bw/Base/_detail/Thread.inl"

}	// namespace thread
}	// namespace bw

#endif BW_BASE_THREAD_H