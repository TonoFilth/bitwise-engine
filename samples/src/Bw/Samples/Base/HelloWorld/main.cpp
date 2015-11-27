#include <iostream>
#include <cstdio>
#include "Bw/Base/Module.h"

using namespace std;
using namespace bw;

int main(int argc, char** argv)
{
    init_base();

	cout << BW_BASE_VERSION_STRING << endl;

    PageAllocator pageAlloc;
    size_t pageSize = system::get_page_size();

    void* mem1 = pageAlloc.allocate(pageSize * 2, 1);
    void* mem2 = pageAlloc.allocate(pageSize * 2, 1);
    void* mem3 = pageAlloc.allocate(pageSize * 1, 1);

    printf("Addr: %p\n", mem1);
    printf("Addr: %p\n", mem2);
    printf("Addr: %p\n", mem3);

    printf("Aligned: %p\n", memory::align_forward(mem1, 2));

    pageAlloc.deallocate(mem1);
    pageAlloc.deallocate(mem2);
    pageAlloc.deallocate(mem3);

    //BW_ASSERT(1 == 2);

	shutdown_base();

	return 0;
}