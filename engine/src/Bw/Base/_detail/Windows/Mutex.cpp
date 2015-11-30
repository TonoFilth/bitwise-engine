#include <Windows.h>
#include "Bw/Base/Multithreading/Mutex.h"
#include "Bw/Base/Memory/Module.h"

namespace bw
{

////////////////////////////////////////////////////////////////////////////////
//  Private types
////////////////////////////////////////////////////////////////////////////////
struct Mutex
{
	Mutex();
	~Mutex();

	CRITICAL_SECTION _mutex;
};

Mutex::Mutex()
{
	InitializeCriticalSection(&_mutex);
}

// -----------------------------------------------------------------------------

Mutex::~Mutex()
{
	DeleteCriticalSection(&_mutex);
}

////////////////////////////////////////////////////////////////////////////////
//  Public functions
////////////////////////////////////////////////////////////////////////////////
Mutex* mutex::create()
{
	return memory::heap_allocator().allocateObject<Mutex>();
}

// -----------------------------------------------------------------------------

void mutex::destroy(Mutex* mutex)
{
	BW_ASSERT(mutex);
	memory::heap_allocator().deallocateObject<Mutex>(mutex);
}

// -----------------------------------------------------------------------------

void mutex::lock(Mutex* m)
{
	BW_ASSERT(m);
	EnterCriticalSection(&m->_mutex);
}

// -----------------------------------------------------------------------------

void mutex::unlock(Mutex* m)
{
	BW_ASSERT(m);
	LeaveCriticalSection(&m->_mutex);
}

}	// namespace bw