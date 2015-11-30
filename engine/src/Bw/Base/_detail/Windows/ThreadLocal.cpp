#include <Windows.h>
#include "Bw/Base/Multithreading/ThreadLocal.h"
#include "Bw/Base/Memory/Module.h"

namespace bw
{

////////////////////////////////////////////////////////////////////////////////
//  Opaque types
////////////////////////////////////////////////////////////////////////////////
struct ThreadLocal
{
	ThreadLocal();
	~ThreadLocal();

	DWORD index;
};

////////////////////////////////////////////////////////////////////////////////
//  Class std functions
////////////////////////////////////////////////////////////////////////////////
ThreadLocal::ThreadLocal() : index(TlsAlloc())
{
}

// -----------------------------------------------------------------------------

ThreadLocal::~ThreadLocal()
{
	TlsFree(index);
}

////////////////////////////////////////////////////////////////////////////////
//  Public functions
////////////////////////////////////////////////////////////////////////////////
ThreadLocal* thread_local::create(void* value)
{
	auto& allocator  = memory::heap_allocator();
	ThreadLocal* tls = allocator.allocateObject<ThreadLocal>();

	if (value)
		thread_local::set_value(*tls, value);

	return tls;
}

// -----------------------------------------------------------------------------

void thread_local::destroy(ThreadLocal& tls)
{
	auto& allocator = memory::heap_allocator();
	allocator.deallocateObject<ThreadLocal>(&tls);
}

// -----------------------------------------------------------------------------

void thread_local::set_value(ThreadLocal& tls, void* value)
{
	TlsSetValue(tls.index, value);
}

// -----------------------------------------------------------------------------

void* thread_local::get_value(ThreadLocal& tls)
{
	return TlsGetValue(tls.index);
}

}	// namespace bw