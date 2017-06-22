#include <list>
#include <random>
#include <Catch/catch.hpp>

#include "bitwise/core/system.h"
#include "bitwise/core/pointer.h"
#include "bitwise/memory/page_allocator.h"

// -----------------------------------------------------------------------------
//  Constants
// -----------------------------------------------------------------------------
static const char* kTestTag = "[page_allocator]";

// -----------------------------------------------------------------------------
//  Test cases
// -----------------------------------------------------------------------------
TEST_CASE("After all allocations/deallocations size is equal to 0", kTestTag)
{
    bw::PageAllocator allocator;
    size_t pageSize = bw::system::page_size();
    std::list<void*> addrList;

    for (int i = 0; i < 1024; ++i)
    {
        addrList.push_back(allocator.allocate(pageSize*2));
    }

    std::default_random_engine generator;

    for (int i = 0; i < 1024; ++i)
    {
        std::uniform_int_distribution<int> distribution(0, 1024-1-i);
        auto it = addrList.begin();
        int indexToRemove = distribution(generator);

        while (indexToRemove-- != 0)
            ++it;

        allocator.deallocate(*it);
        addrList.erase(it);
    }

    REQUIRE(allocator.allocatedSize() == 0);
}

// -----------------------------------------------------------------------------

TEST_CASE("Memory addresses are aligned to the system page size", kTestTag)
{
    size_t pageSize = bw::system::page_size();
    void*  memory   = nullptr;

    bw::PageAllocator allocator;

    memory = allocator.allocate(pageSize);
    REQUIRE(bw::pointer::is_aligned(memory, pageSize));
    
    allocator.deallocate(memory);
}

// -----------------------------------------------------------------------------

TEST_CASE("Requested memory size is rounded up and page aligned", kTestTag)
{
    
}