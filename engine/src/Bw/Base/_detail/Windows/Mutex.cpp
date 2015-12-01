#include <Windows.h>
#include "Bw/Base/Multithreading/Mutex.h"
#include "Bw/Base/_detail/MultithreadingInternal.h"
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

}	// namespace bw

namespace
{
	using namespace bw;

	PoolAllocator<Mutex>* _MutexPool = nullptr;

}	// Private namespace

namespace bw
{
namespace internal
{
	void init_mutex_pool()    { _MutexPool = memory::page_allocator().allocateObject<PoolAllocator<Mutex>>(); }
	void destroy_mutex_pool() { memory::page_allocator().deallocateObject(_MutexPool); }

}	// namespace internal

////////////////////////////////////////////////////////////////////////////////
//  Public functions
////////////////////////////////////////////////////////////////////////////////
Mutex* mutex::create()
{
	return _MutexPool->next();
}

// -----------------------------------------------------------------------------

void mutex::destroy(Mutex* mutex)
{
	BW_ASSERT(mutex);

	_MutexPool->collect(mutex);
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