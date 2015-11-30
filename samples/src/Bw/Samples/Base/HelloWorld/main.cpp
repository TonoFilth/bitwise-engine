#include <iostream>
#include <cstdio>
#include <unordered_map>
#include "Bw/Base/Module.h"

using namespace std;
using namespace bw;

void test()
{
	ScopeAllocator256 salloc;

	unordered_map<int, int>* mymap1 = salloc.allocateObject<unordered_map<int, int>>();
	string* mymap2 = salloc.allocateObject<string>();
}

void free_func(void* data)
{

}

struct TestFunctor
{
	void operator() (void* data)
	{

	}
};

class Task
{
public:
	void run(void* data)
	{
	}
};

int main(int argc, char** argv)
{
	ThreadLocal* tls0 = thread_local::create();
	ThreadLocal* tls1 = thread_local::create();

	TestFunctor functor;
	Task task;

	Thread* t0 = thread::create(functor,    nullptr);
	Thread* t1 = thread::create(&Task::run, nullptr, &task);
	Thread* t2 = thread::create(free_func,  nullptr);

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

	test();

	return 0;
}