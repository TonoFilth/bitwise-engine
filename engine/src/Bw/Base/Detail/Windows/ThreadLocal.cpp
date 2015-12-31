#include <Windows.h>
#include "Bw/Base/Multithreading/ThreadLocal.h"
#include "Bw/Base/Memory.h"

namespace bw
{

////////////////////////////////////////////////////////////////////////////////
//  Public functions
////////////////////////////////////////////////////////////////////////////////
ThreadLocalIndex thread_local::create(void* value)
{
	ThreadLocalIndex tls = TlsAlloc();

	thread_local::set_value(tls, value);

	return tls;
}

// -----------------------------------------------------------------------------

void thread_local::destroy(ThreadLocalIndex tls)
{
	TlsFree(static_cast<DWORD>(tls));
}

// -----------------------------------------------------------------------------

void thread_local::set_value(ThreadLocalIndex tls, void* value)
{
	TlsSetValue(static_cast<DWORD>(tls), value);
}

// -----------------------------------------------------------------------------

void* thread_local::get_value(ThreadLocalIndex tls)
{
	return TlsGetValue(static_cast<DWORD>(tls));
}

}	// namespace bw