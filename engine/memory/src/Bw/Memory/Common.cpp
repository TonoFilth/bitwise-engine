#include "Bw/Memory/Common.h"
#include "Bw/Base/Assert.h"
#include "Bw/Memory/MallocAllocator.h"
#include "Bw/Memory/PageAllocator.h"

namespace bw
{
namespace Internal
{

////////////////////////////////////////////////////////////////////////////////
//  Private variables
////////////////////////////////////////////////////////////////////////////////
extern MallocAllocator* s_GlobalAllocator;
extern MallocAllocator* s_DebugAllocator;
extern PageAllocator*   s_PageAllocator;

extern void InitializeMemoryModule();

}	// namespace Internal

////////////////////////////////////////////////////////////////////////////////
//  Public functions
////////////////////////////////////////////////////////////////////////////////
Allocator& Memory::GlobalAllocator()
{
	if (!Internal::s_GlobalAllocator)
		Internal::InitializeMemoryModule();

    return *Internal::s_GlobalAllocator;
}

// -----------------------------------------------------------------------------

Allocator& Memory::SystemAllocator()
{
	if (!Internal::s_PageAllocator)
		Internal::InitializeMemoryModule();

	return *Internal::s_PageAllocator;
}

// -----------------------------------------------------------------------------

Allocator& Memory::DebugAllocator()
{
	if (!Internal::s_DebugAllocator)
		Internal::InitializeMemoryModule();

	return *Internal::s_DebugAllocator;
}

}	// namespace bw