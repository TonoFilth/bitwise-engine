#include "Bw/Base/Memory/TCMallocAllocator.h"
#include "Bw/Base/Memory/ModuleInit.h"
#include "Bw/Base/Multithreading/Thread.h"
#include "Bw/Base/Multithreading/ThreadLocal.h"

namespace
{

using namespace bw;

////////////////////////////////////////////////////////////////////////////////
//  Typedefs
////////////////////////////////////////////////////////////////////////////////
struct Span;
class  ThreadCache;
class  CentralHeap;

////////////////////////////////////////////////////////////////////////////////
//  Private constants
////////////////////////////////////////////////////////////////////////////////
const size_t SMALL_OBJECT_SIZE = 1024 * 32;

////////////////////////////////////////////////////////////////////////////////
//  Private variables
////////////////////////////////////////////////////////////////////////////////
ThreadLocal<ThreadCache> _ThreadCache;

////////////////////////////////////////////////////////////////////////////////
//  ThreadCache
////////////////////////////////////////////////////////////////////////////////
class ThreadCache
{
public:
	ThreadCache(CentralHeap* centralHeap) :
		m_centralHeap(centralHeap)
	{
	}

	void* allocate(size_t size, size_t alignment)
	{
		size_t index = getClassIndex(size);

		if (m_classList[index] == NULL)
		{
			// Fetch from central heap
		}
		else
		{
			// Return the requested memory
		}

		return NULL;
	}

private:
	size_t getClassIndex(size_t size) const
	{
		return 0;
	}

private:
	CentralHeap* m_centralHeap;
	void*        m_classList[170];
};

////////////////////////////////////////////////////////////////////////////////
//  CentralHeap
////////////////////////////////////////////////////////////////////////////////
class CentralHeap
{
public:
	CentralHeap()
	{

	}

private:
	Span* m_span[128];
};

////////////////////////////////////////////////////////////////////////////////
//  Span
////////////////////////////////////////////////////////////////////////////////
struct Span
{
	size_t sizeClass;
	size_t pageCount;
};

CentralHeap* _CentralHeap = NULL;

}	// private namespace

namespace bw
{

////////////////////////////////////////////////////////////////////////////////
//  Class std functions
////////////////////////////////////////////////////////////////////////////////
TCMallocAllocator::TCMallocAllocator()
{
}

// -----------------------------------------------------------------------------

TCMallocAllocator::~TCMallocAllocator()
{
}

////////////////////////////////////////////////////////////////////////////////
//  Private functions
////////////////////////////////////////////////////////////////////////////////
void* TCMallocAllocator::allocateSmallObject(size_t size, size_t alignment)
{
	ThreadCache* cache = _ThreadCache;
	
	return cache->allocate(size, alignment);
}

// -----------------------------------------------------------------------------

void* TCMallocAllocator::allocateLargeObject(size_t size, size_t alignment)
{
	return NULL;
}

////////////////////////////////////////////////////////////////////////////////
//  Public functions
////////////////////////////////////////////////////////////////////////////////
void* TCMallocAllocator::allocate(size_t size, size_t alignment)
{
	if (_ThreadCache.isNull())
	{
		// If we are the main thread create the central heap
		if (thread::main_thread_id() == thread::thread_id())
		{
			_CentralHeap = (CentralHeap*) memory::page_allocator().allocateObject<CentralHeap>();
		}

		_ThreadCache = (ThreadCache*) memory::page_allocator().allocateObject<ThreadCache>(_CentralHeap);
	}
	
	if (size <= SMALL_OBJECT_SIZE)
		allocateSmallObject(size, alignment);
	else
		allocateLargeObject(size, alignment);

	return NULL;
}

// -----------------------------------------------------------------------------

void TCMallocAllocator::deallocate(void* data)
{

}

// -----------------------------------------------------------------------------

size_t TCMallocAllocator::allocatedSize() const
{
	return 0;
}

// -----------------------------------------------------------------------------

size_t TCMallocAllocator::allocatedSize(void* data) const
{
	return 0;
}

}	// namespace bw