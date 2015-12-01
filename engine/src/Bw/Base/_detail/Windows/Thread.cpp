#include <Windows.h>
#include <process.h>
#include "Bw/Base/Multithreading/Thread.h"
#include "Bw/Base/Memory/Module.h"

namespace bw
{
	struct Thread
	{
		internal::ThreadEntryPoint* entryPoint;
		HANDLE thread;
	};

}	// namespace bw

namespace
{
	using namespace bw;

	PoolAllocator<Thread>* _ThreadPool = nullptr;

}	// Private namespace

namespace bw
{

////////////////////////////////////////////////////////////////////////////////
//  Class std functions
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
//  Public functions
////////////////////////////////////////////////////////////////////////////////
namespace internal
{
	Thread* create_thread(ThreadEntryPoint& entryPoint)
	{
		Thread* t = _ThreadPool->next();

		t->entryPoint = &entryPoint;

		return t;
	}

	void init_thread_pool()    { _ThreadPool = memory::page_allocator().allocateObject<PoolAllocator<Thread>>(); }
	void destroy_thread_pool() { memory::page_allocator().deallocateObject(_ThreadPool); }

}	// namespace internal

void thread::destroy(Thread* thread)
{
	BW_ASSERT(thread);
	_ThreadPool->collect(thread);
}

// -----------------------------------------------------------------------------

void thread::run(Thread* thread)
{
	BW_ASSERT(thread);
}

}	// namespace bw