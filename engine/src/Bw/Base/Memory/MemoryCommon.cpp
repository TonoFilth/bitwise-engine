#include "Bw/Base/Memory/Common.h"
#include "Bw/Base/Memory/HeapAllocator.h"
#include "Bw/Base/Memory/PageAllocator.h"

namespace bw
{
namespace Internal
{

////////////////////////////////////////////////////////////////////////////////
//  Private variables
////////////////////////////////////////////////////////////////////////////////
extern HeapAllocator* s_StaticHeap;
extern HeapAllocator* s_GlobalHeap;
extern HeapAllocator* s_DebugAllocator;
extern PageAllocator* s_PageAllocator;

}	// namespace Internal

////////////////////////////////////////////////////////////////////////////////
//  Public functions
////////////////////////////////////////////////////////////////////////////////
Allocator& Memory::GlobalAllocator()
{
    return *Internal::s_GlobalHeap;
}

// -----------------------------------------------------------------------------

Allocator& Memory::SystemAllocator()
{
    return *Internal::s_PageAllocator;
}

// -----------------------------------------------------------------------------

Allocator& Memory::DebugAllocator()
{
	return *Internal::s_DebugAllocator;
}

}	// namespace bw