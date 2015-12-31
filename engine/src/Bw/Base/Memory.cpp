#include <new>
#include "Bw/Base/Memory.h"
#include "Bw/Base/Common/Assert.h"

namespace bw
{

////////////////////////////////////////////////////////////////////////////////
//  Private constants
////////////////////////////////////////////////////////////////////////////////
const size_t BUFFER_SIZE = 1024;    // Bytes

////////////////////////////////////////////////////////////////////////////////
//  Private variables
////////////////////////////////////////////////////////////////////////////////
static char s_Buffer[BUFFER_SIZE];

namespace Internal
{

HeapAllocator* s_StaticHeap     = nullptr;
HeapAllocator* s_GlobalHeap     = nullptr;
HeapAllocator* s_DebugAllocator = nullptr;
PageAllocator* s_PageAllocator  = nullptr;

}	// namespace Internal

////////////////////////////////////////////////////////////////////////////////
//  Private functions
////////////////////////////////////////////////////////////////////////////////
static void InitAllocators()
{
    // Make sure the memory system wasn't initialized
    BW_ASSERT(Internal::s_StaticHeap == nullptr);

    Internal::s_StaticHeap = new (s_Buffer) HeapAllocator(nullptr, s_Buffer + sizeof(HeapAllocator),
        BUFFER_SIZE - sizeof(HeapAllocator));

    Internal::s_PageAllocator = Internal::s_StaticHeap->allocateObject<PageAllocator>();
    //_GlobalHeap    = _StaticHeap->allocateObject<HeapAllocator>(*_PageAllocator, config.globalHeap);
}

////////////////////////////////////////////////////////////////////////////////
//  Public functions
////////////////////////////////////////////////////////////////////////////////
void Internal::InitMemory()
{
    InitAllocators();
}

// -----------------------------------------------------------------------------

void Internal::QuitMemory()
{
	// Make sure the memory system was initialized
    BW_ASSERT(s_StaticHeap != nullptr);

    s_StaticHeap->deallocateObject<HeapAllocator>(s_GlobalHeap);
    s_GlobalHeap = nullptr;

    s_StaticHeap->deallocateObject<PageAllocator>(s_PageAllocator);
    s_PageAllocator = nullptr;

    s_StaticHeap->~HeapAllocator();
    s_StaticHeap = nullptr;
}

}	// namespace bw