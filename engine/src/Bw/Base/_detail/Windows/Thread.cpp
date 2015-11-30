#include <Windows.h>
#include <process.h>
#include "Bw/Base/Multithreading/Thread.h"
#include "Bw/Base/Memory/Module.h"

namespace bw
{

struct Thread
{
	ThreadEntryPoint* entryPoint;
	HANDLE thread;
};

////////////////////////////////////////////////////////////////////////////////
//  Class std functions
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
//  Public functions
////////////////////////////////////////////////////////////////////////////////
Thread* thread::create(ThreadEntryPoint& entryPoint)
{
	Thread* t = memory::heap_allocator().allocateObject<Thread>();

	t->entryPoint = &entryPoint;
	return t;
}

// -----------------------------------------------------------------------------

void thread::destroy(Thread* thread)
{
	BW_ASSERT(thread);
	memory::heap_allocator().deallocateObject<Thread>(thread);
}

// -----------------------------------------------------------------------------

void thread::run(Thread* thread)
{
	BW_ASSERT(thread);
}

}	// namespace bw