#include <cstring>	// memcpy()
#include "Bw/Memory/PageAllocator.h"
#include "Bw/Memory/Common.h"
#include "Bw/Base/System.h"
#include "Bw/Base/Integer.h"
#include "Bw/Base/Assert.h"

#if defined(BW_SYSTEM_WINDOWS)
#	include "Bw/Memory/Windows/SysAlloc.h"
#else
#	include "Bw/Memory/Unix/SysAlloc.h"
#endif

#if defined(BW_DEBUG)
#	include "Bw/Base/Console.h"
#endif

////////////////////////////////////////////////////////////////////////////////
//  Macros
////////////////////////////////////////////////////////////////////////////////
#define get_node(list, offset) (AllocationNode*) bw::Memory::PointerAdd(list, sizeof(AllocationList) + offset * sizeof(AllocationNode))

namespace
{

using namespace bw;

////////////////////////////////////////////////////////////////////////////////
//  Typedefs
////////////////////////////////////////////////////////////////////////////////
typedef uint16_t offset_t;

////////////////////////////////////////////////////////////////////////////////
//  Private variables
////////////////////////////////////////////////////////////////////////////////
size_t s_PageSize = 0;

////////////////////////////////////////////////////////////////////////////////
//  Private types
////////////////////////////////////////////////////////////////////////////////
struct AllocationNode
{
	void*    data;
	uint16_t pageCount;
	offset_t next;
};

// -----------------------------------------------------------------------------

struct AllocationList
{
	static const offset_t kInvalidOffset = Integer::kUint16Max;

	size_t used;		// Number of items in use
	size_t capacity;	// Maximum number of items this list can hold

	offset_t first;
	offset_t last;
	offset_t free;

	uint8_t pageCount;	// Number of pages used by the list
};

#if defined(BW_DEBUG)
void dump(AllocationList*);
#endif

////////////////////////////////////////////////////////////////////////////////
//  Private functions
////////////////////////////////////////////////////////////////////////////////
BW_INLINE size_t size_to_pages(size_t size)
{
	size_t remainder = size % s_PageSize;
	size_t result    = size / s_PageSize;

	return (remainder == 0 ? result : result + 1);
}

// -----------------------------------------------------------------------------

void create_free_list(AllocationList* list, offset_t first, offset_t last)
{
	offset_t currentOffset = first;

	while (currentOffset < last)
	{
		AllocationNode* freeNode = get_node(list, currentOffset);

		freeNode->data      = nullptr;
		freeNode->pageCount = 0;
			
		currentOffset++;
			
		if (currentOffset < last)
			freeNode->next = currentOffset;
		else
			freeNode->next = AllocationList::kInvalidOffset;
	}
}

// -----------------------------------------------------------------------------

AllocationList* create_list(size_t size)
{
	AllocationList* list = (AllocationList*) Internal::SysAlloc(size);
	BW_ASSERT(list);

	list->first     = AllocationList::kInvalidOffset;
	list->last      = AllocationList::kInvalidOffset;
	list->free      = 0;
	list->used      = 0;
	list->capacity  = (size - sizeof(AllocationList)) / sizeof(AllocationNode);
	list->pageCount = static_cast<uint8_t>(size_to_pages(size));

	create_free_list(list, 0, static_cast<offset_t>(list->capacity));
	
	return list;
}

// -----------------------------------------------------------------------------

AllocationNode create_node(size_t dataSize, size_t alignment)
{
	AllocationNode node;

	// Round to upper page bound
	const uint16_t pageCount = static_cast<uint16_t>(size_to_pages(dataSize));
	dataSize = pageCount * s_PageSize;

	//BW_ASSERT(Integer::IsMultipleOf(dataSize, s_PageSize) && Integer::IsPowerOf2(alignment));

	void* data = Internal::SysAlloc(dataSize);

	// We expect data to be properly aligned
	BW_ASSERT(data && Memory::IsAligned(data, alignment));

	node.next      = AllocationList::kInvalidOffset;
	node.data      = data;
	node.pageCount = pageCount;

	return node;
}

// -----------------------------------------------------------------------------

AllocationList* list_expand(AllocationList* list, size_t expandSize)
{
	const size_t pageCount = size_to_pages(expandSize);
	BW_ASSERT(static_cast<size_t>(list->pageCount) + pageCount <= 0xFF);

	const size_t totalSize = list->pageCount * s_PageSize + expandSize;

	AllocationList* newList = (AllocationList*) Internal::SysAlloc(totalSize);

	::memcpy(newList, list, list->pageCount * s_PageSize);
	//memcpy_s(newList, totalSize, list, list->pageCount * s_PageSize);

	newList->capacity  = (totalSize - sizeof(AllocationList)) / sizeof(AllocationNode);
	newList->free      = static_cast<offset_t>(list->capacity);
	newList->pageCount = list->pageCount + newList->pageCount;

	// Add nodes to free list
	create_free_list(newList, newList->free, static_cast<offset_t>(newList->capacity));
	Internal::SysFree(list, list->pageCount * s_PageSize);

#if defined(BW_DEBUG)
	dump(newList);
#endif

	return newList;
}

// -----------------------------------------------------------------------------

void list_push_back(AllocationList* list, AllocationNode& node)
{
	// Make sure there are some free nodes
	BW_ASSERT(list->free != AllocationList::kInvalidOffset);

	offset_t newNodeOffset  = list->free;
	AllocationNode* newNode = get_node(list, newNodeOffset);;

	// Copy node data
	newNode->data      = node.data;
	newNode->pageCount = node.pageCount;

	if (list->first == AllocationList::kInvalidOffset)	// Empty list
	{
		list->first = newNodeOffset;
	}
	else
	{
		AllocationNode* lastNode = get_node(list, list->last);
		lastNode->next = newNodeOffset;
	}

	list->last  = newNodeOffset;
	list->free  = newNode->next;	// Push next free node at the start of the free list
	list->used += 1;

	newNode->next = AllocationList::kInvalidOffset;
}

// -----------------------------------------------------------------------------

bool find_node(AllocationList* list, void* data, offset_t& node, offset_t& prev)
{
	offset_t nodeOffset = list->first;
	offset_t prevOffset = AllocationList::kInvalidOffset;

	AllocationNode* n = get_node(list, nodeOffset);
	
	while (nodeOffset != AllocationList::kInvalidOffset && n->data != data)
	{
		prevOffset = nodeOffset;
		nodeOffset = n->next;
		n = get_node(list, nodeOffset);
	}

	node = nodeOffset;
	prev = prevOffset;

	return (nodeOffset != AllocationList::kInvalidOffset);
}

// -----------------------------------------------------------------------------

#if defined(BW_DEBUG)

void dump(AllocationList* list)
{
	Console::Write("PageAllocator list\n");

	if (list->first != AllocationList::kInvalidOffset)
	{
		Console::WriteFormat(" - First: %u\n", list->first);
		Console::WriteFormat(" - Last:  %u\n", list->last);
	}
	else
	{
		Console::Write(" - First: -\n");
		Console::Write(" - Last:  -\n");
	}

	if (list->free != AllocationList::kInvalidOffset)
		Console::WriteFormat(" - Free:  %u\n\n", list->free);
	else
		Console::Write(" - Free:  -\n\n");

	Console::WriteFormat(" - Capacity: %lu\n", list->capacity);
	Console::WriteFormat(" - Used:     %lu\n", list->used);
	Console::WriteFormat(" - Size:     %lu\n", list->pageCount * s_PageSize);
	Console::Write("\nNodes:\n");

	offset_t nodeOffset = list->first;

	while (nodeOffset != AllocationList::kInvalidOffset)
	{
		AllocationNode* node = get_node(list, nodeOffset);

		Console::WriteFormat(" %u -> pages:%u size:%lu data:%p\n", nodeOffset, node->pageCount, node->pageCount * s_PageSize, node->data);
		nodeOffset = node->next;
	}

	Console::Write("\nFree Nodes:\n");

	offset_t freeOffset = list->free;
	
	if (freeOffset == AllocationList::kInvalidOffset)
		Console::Write("<empty>");
	else
		Console::WriteFormat("%u-", freeOffset);

	while (freeOffset != AllocationList::kInvalidOffset)
	{
		AllocationNode* freeNode = get_node(list, freeOffset);

		if (freeNode->next != AllocationList::kInvalidOffset)
			Console::WriteFormat("%u-", freeNode->next);
		else
			Console::Write("END");
		
		freeOffset = freeNode->next;
	}

	Console::WriteLine("");
}

#endif	// BW_DEBUG

}   // private namespace

namespace bw
{

////////////////////////////////////////////////////////////////////////////////
//  Class std functions
////////////////////////////////////////////////////////////////////////////////
PageAllocator::PageAllocator() :
	m_list(nullptr),
    m_totalAllocated(0)
{
    // The first instance of the PageAllocator class must save the
    // system page size
    if (s_PageSize == 0)
    {
        s_PageSize = System::GetPageSize();

        // Make sure the page size is valid
        BW_ASSERT(s_PageSize > 0);
    }
}

// -----------------------------------------------------------------------------

PageAllocator::~PageAllocator()
{
	if (m_list)
	{
		AllocationList* list   = (AllocationList*) m_list;
		const size_t sizeBytes = list->pageCount * s_PageSize;

		m_totalAllocated -= sizeBytes;

		Internal::SysFree(list, sizeBytes);
		m_list = nullptr;
	}

	// Forgot to deallocate some pages?
    BW_ASSERT(m_totalAllocated == 0);
}

////////////////////////////////////////////////////////////////////////////////
//  Public functions
////////////////////////////////////////////////////////////////////////////////
void* PageAllocator::allocate(size_t size, size_t alignment)
{
	AllocationList* list = nullptr;
	
	if (m_list)
	{
		list = (AllocationList*) m_list;
	}
	else
	{
		const size_t initialSize = s_PageSize;

		list   = create_list(initialSize);
		m_list = list;
		m_totalAllocated += initialSize;
	}

	// Expand list when full
	if (list->used >= list->capacity)
	{
#if defined(BW_DEBUG)
		dump(list);
#endif

		list   = list_expand(list, s_PageSize);
		m_list = list;
		m_totalAllocated += s_PageSize;
	}

	AllocationNode node = create_node(size, alignment);
	list_push_back(list, node);

	m_totalAllocated += node.pageCount * s_PageSize;

	return node.data;
}

// -----------------------------------------------------------------------------

void PageAllocator::deallocate(void* data)
{
	AllocationList* list = (AllocationList*) m_list;
	offset_t nodeOffset  = AllocationList::kInvalidOffset;
	offset_t prevOffset  = AllocationList::kInvalidOffset;

	find_node(list, data, nodeOffset, prevOffset);

	// data pointer not allocated through this allocator
	BW_ASSERT(nodeOffset != AllocationList::kInvalidOffset);

	AllocationNode* node = get_node(m_list, nodeOffset);
	AllocationNode* next = (node->next == AllocationList::kInvalidOffset ? nullptr : get_node(m_list, node->next));

	// Node is the unique node in the list
	if (nodeOffset == list->first && nodeOffset == list->last)
	{
		list->first = AllocationList::kInvalidOffset;
		list->last  = AllocationList::kInvalidOffset;
	}
	else if (nodeOffset == list->first)	// Node is the first item in the list
	{
		list->first = node->next;
	}
	else if (nodeOffset == list->last)		// Node is the last item in the list
	{
		AllocationNode* last = get_node(m_list, prevOffset);

		list->last = prevOffset;
		last->next = AllocationList::kInvalidOffset;
	}
	else									// Node is an intermediary item in the list
	{
		AllocationNode* last = get_node(m_list, prevOffset);
		last->next = node->next;
	}

	size_t size = node->pageCount * s_PageSize;

	m_totalAllocated -= size;
	Internal::SysFree(node->data, size);

	offset_t prevFreeNodeOffset = list->free;

	list->free = nodeOffset;
	node->next = prevFreeNodeOffset;

	list->used -= 1;
}

// -----------------------------------------------------------------------------

size_t PageAllocator::allocatedSize() const
{
	return m_totalAllocated;
}

// -----------------------------------------------------------------------------

size_t PageAllocator::allocatedSize(void* data) const
{
	AllocationList* list = (AllocationList*) m_list;
	offset_t nodeOffset  = AllocationList::kInvalidOffset;
	offset_t prevOffset  = AllocationList::kInvalidOffset;

	if (find_node(list, data, nodeOffset, prevOffset))
	{
		AllocationNode* node = get_node(m_list, nodeOffset);
		return node->pageCount * s_PageSize;
	}
	else
	{
		return Allocator::kSizeNotTracked;
	}
}

}   // namespace bw