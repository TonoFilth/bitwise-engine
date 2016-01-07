#include <new>		// placement new
#include <cstdlib>	// atexit()

#include "Bw/Memory.h"
#include "Bw/Base/Assert.h"

namespace bw
{

////////////////////////////////////////////////////////////////////////////////
//  Private constants
////////////////////////////////////////////////////////////////////////////////
const size_t kBufferSize = 1024; // Bytes

////////////////////////////////////////////////////////////////////////////////
//  Private variables
////////////////////////////////////////////////////////////////////////////////
static bool s_Initialized   = false;
static bool s_FirstTimeInit = true;

static char s_Buffer[kBufferSize];
static MallocAllocator* s_StaticHeap = nullptr;

namespace Internal
{
	MallocAllocator* s_GlobalAllocator = nullptr;
	MallocAllocator* s_DebugAllocator  = nullptr;
	PageAllocator*   s_PageAllocator   = nullptr;

}	// namespace Internal

////////////////////////////////////////////////////////////////////////////////
//  Private functions
////////////////////////////////////////////////////////////////////////////////
static void InitAllocators()
{
    // Make sure the memory module wasn't initialized
    BW_ASSERT(s_StaticHeap == nullptr);

    s_StaticHeap = new (s_Buffer) MallocAllocator();

    Internal::s_PageAllocator   = s_StaticHeap->allocateObject<PageAllocator>();
	Internal::s_GlobalAllocator = s_StaticHeap->allocateObject<MallocAllocator>();
    Internal::s_DebugAllocator  = s_StaticHeap->allocateObject<MallocAllocator>();
}

////////////////////////////////////////////////////////////////////////////////
//  Public functions
////////////////////////////////////////////////////////////////////////////////
void Internal::InitializeMemoryModule()
{
	// If memory module was already initialized, do nothing
	if (s_Initialized)
		return;

	InitAllocators();
	s_Initialized = true;

	// Make sure memory module is shutdown
	if (s_FirstTimeInit)
	{
		s_FirstTimeInit = false;
		atexit(Internal::ShutdownMemoryModule);
	}
}

// -----------------------------------------------------------------------------

void Internal::ShutdownMemoryModule()
{
	// If memory module wasn't initialized, do nothing
   if (!s_Initialized)
	   return;

    s_StaticHeap->deallocateObject(s_GlobalAllocator);
    s_GlobalAllocator = nullptr;

    s_StaticHeap->deallocateObject(s_PageAllocator);
    s_PageAllocator = nullptr;

    s_StaticHeap->~MallocAllocator();
    s_StaticHeap = nullptr;

	s_Initialized = false;
}

}	// namespace bw