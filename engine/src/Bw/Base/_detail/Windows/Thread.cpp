#include <Windows.h>
#include <process.h>
#include "Bw/Base/Multithreading/Thread.h"
#include "Bw/Base/Memory/Module.h"

namespace bw
{
	struct Thread
	{
		internal::ThreadEntryPoint* _entryPoint;
		unsigned int _id;
		HANDLE       _handle;
	};

}	// namespace bw

namespace
{
	using namespace bw;

	PoolAllocator<Thread>* _ThreadPool = nullptr;

	unsigned int _stdcall thread_main(void* data)
	{
		Thread* thread = (Thread*) data;

		thread->_entryPoint->run(nullptr);

		_endthreadex(0);

		return 0;
	}

}	// Private namespace

namespace bw
{

////////////////////////////////////////////////////////////////////////////////
//  Public functions
////////////////////////////////////////////////////////////////////////////////
namespace internal
{
	Thread* create_thread(ThreadEntryPoint& entryPoint)
	{
		Thread* t = _ThreadPool->next();

		t->_entryPoint = &entryPoint;

		return t;
	}

	void init_thread_pool()    { _ThreadPool = memory::page_allocator().allocateObject<PoolAllocator<Thread>>(); }
	void destroy_thread_pool() { memory::page_allocator().deallocateObject(_ThreadPool); }

}	// namespace internal

void thread::destroy(Thread* thread)
{
	BW_ASSERT(thread);
	memory::page_allocator().deallocateObject(thread->_entryPoint);
	_ThreadPool->collect(thread);
}

// -----------------------------------------------------------------------------

void thread::run(Thread* thread)
{
	BW_ASSERT(thread);

	thread->_handle = (HANDLE) _beginthreadex(NULL, 0, thread_main, thread, 0, &thread->_id);
}

// -----------------------------------------------------------------------------

void thread::wait(Thread* thread)
{
	BW_ASSERT(thread && thread->_id != GetCurrentThreadId());

	WaitForSingleObject(thread->_handle, INFINITE);
}

// -----------------------------------------------------------------------------

void thread::terminate(Thread* thread)
{
	BW_ASSERT(thread);

	TerminateThread(thread->_handle, 0);
}

}	// namespace bw