#include <Windows.h>
#include "Bw/Base/Memory/PageAllocator.h"
#include "Bw/Base/Memory/PointerArithmetic.h"
#include "Bw/Base/Memory/MemoryUtils.h"
#include "Bw/Base/System.h"
#include "Bw/Base/Integer.h"

namespace
{

using namespace bw;

////////////////////////////////////////////////////////////////////////////////
//  Private variables
////////////////////////////////////////////////////////////////////////////////
size_t s_PageSize = 0;

////////////////////////////////////////////////////////////////////////////////
//  Private types
////////////////////////////////////////////////////////////////////////////////
struct AllocationNode
{
	void*           data;
	size_t          size;
	AllocationNode* next;

	bool operator=(const AllocationNode& other)
	{
		return data == other.data;
	}
};

// -----------------------------------------------------------------------------

struct AllocationList
{
	AllocationNode* first;
	AllocationNode* last;

	size_t sizeBytes;
};

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

AllocationList* create_list(size_t size)
{
	AllocationList* list = (AllocationList*) VirtualAlloc(nullptr, size, MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);
	BW_ASSERT(list);

	list->first = nullptr;
	list->last  = nullptr;
	list->sizeBytes = size;

	return list;
}

// -----------------------------------------------------------------------------

bool find_node(AllocationList* list, void* data, AllocationNode** node, AllocationNode** prev)
{
	BW_ASSERT(node);

	AllocationNode* n = list->first;
	AllocationNode* p = nullptr;

	while (n && n->data != data)
	{
		p = n;
		n = n->next;
	}

	*node = n;

	if (prev)
		*prev = p;

	return (n != nullptr);
}

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
        s_PageSize = system::get_page_size();

        // Make sure the page size is valid
        BW_ASSERT(s_PageSize > 0);
    }
}

// -----------------------------------------------------------------------------

PageAllocator::~PageAllocator()
{
	if (m_list)
	{
		AllocationList* list = (AllocationList*) m_list;
		m_totalAllocated -= list->sizeBytes;

		VirtualFree(list, list->sizeBytes, MEM_RELEASE);
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
	// Round to upper page bound
	size = size_to_pages(size) * s_PageSize;

	BW_ASSERT(integer::is_multiple_of(size, s_PageSize) && integer::is_power_of_2(alignment));

	AllocationNode* node = nullptr;

	if (m_list == nullptr)
	{
		const size_t listSize = s_PageSize;

		AllocationList* list = create_list(listSize);
		node = (AllocationNode*) memory::pointer_add(list, sizeof(AllocationList));

		list->first = node;
		list->last  = node;

		m_list = list;
		m_totalAllocated += listSize;
	}
	else
	{
		// TODO: Check that list is not exhausted

		AllocationList* list = (AllocationList*) m_list;
		node = (AllocationNode*) memory::pointer_add(list->last, sizeof(AllocationNode));

		list->last->next = node;
		list->last       = node;
	}

	void* data = VirtualAlloc(nullptr, size, MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);

	// We expect data to be aligned properly
	BW_ASSERT(memory::is_aligned(data, alignment));

	node->next = nullptr;
	node->size = size;
	node->data = data;

	m_totalAllocated += size;

	return data;
}

// -----------------------------------------------------------------------------

void PageAllocator::deallocate(void* data)
{
	AllocationList* list = (AllocationList*) m_list;
	AllocationNode* node = nullptr;
	AllocationNode* prev = nullptr;

	find_node(list, data, &node, &prev);

	// data pointer not allocated through this allocator
	BW_ASSERT(node);

	AllocationNode* next = node->next;

	// Node is the unique node in the list
	if (node == list->first && node == list->last)
	{
		list->first = nullptr;
		list->last  = nullptr;
	}
	else if (node == list->first)	// Node is the first node in the list
	{
		list->first = next;
	}
	else if (node == list->last)
	{
		list->last = prev;
		prev->next = nullptr;
	}
	else
	{
		prev->next = next;
	}

	m_totalAllocated -= node->size;
	VirtualFree(node->data, node->size, MEM_RELEASE);
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
	AllocationNode* node = nullptr;

	if (find_node(list, data, &node, nullptr))
	{
		return node->size;
	}
	else
	{
		return Allocator::kSizeNotTracked;
	}
}

}   // namespace bw