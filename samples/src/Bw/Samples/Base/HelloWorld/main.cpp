#include <iostream>
#include <cstdio>
#include <unordered_map>
#include "Bw/Base/Module.h"

using namespace std;
using namespace bw;

int main(int argc, char** argv)
{
    init_base();

	cout << BW_BASE_VERSION_STRING << endl;

	auto& palloc = memory::page_allocator();

	void* mem1 = palloc.allocate(system::get_page_size() - 1);
	void* mem2 = palloc.allocate(system::get_page_size() + 1);

	cout << "mem1 size: " << palloc.allocatedSize(mem1) << endl;
	cout << "mem2 size: " << palloc.allocatedSize(mem2) << endl;
	cout << "total size: " << palloc.allocatedSize()    << endl;

	palloc.deallocate(mem1);
	palloc.deallocate(mem2);

    //BW_ASSERT(1 == 2);

	shutdown_base();

	return 0;
}