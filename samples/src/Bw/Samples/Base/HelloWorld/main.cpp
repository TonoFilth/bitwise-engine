#include <iostream>
#include <cstdio>
#include <unordered_map>
#include <Windows.h>
#include "Bw/Base/Module.h"

using namespace std;
using namespace bw;

#pragma comment(lib, "winmm.lib")

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

ThreadLocal<int> g_local;

class Task
{
public:
	Task(int start, int end) :
		m_mutex(mutex::create()),
		m_start(start),
		m_end(end)
	{
	}

	~Task()
	{
		mutex::destroy(m_mutex);
	}

	void run(void* data)
	{
		/*cout << "Running from a thread :)" << endl;
		cout << "Is Null? " << g_local.isNull() << endl;

		int count = m_start;
		g_local = &count;

		while (count < m_end)
		{
			Lock lock(*m_mutex);
			
			cout << GetCurrentThreadId() << " | MyLocalVar: " << *g_local << "\n";

			count++;
		}*/


		// Get the supported timer resolutions on this system
		//TIMECAPS tc;
		//timeGetDevCaps(&tc, sizeof(TIMECAPS));

		//// Set the timer resolution to the minimum for the Sleep call
		//timeBeginPeriod(tc.wPeriodMin);

		//// Wait...
		//::Sleep(5000);

		//// Reset the timer resolution back to the system default
		//timeEndPeriod(tc.wPeriodMin);
	}

private:
	Mutex* m_mutex;
	int    m_start;
	int    m_end;
};

class MyClass
{
public:
	MyClass() :
		m_value(0)
	{
	}

	explicit MyClass(int32_t value) :
		m_value(value)
	{
	}

	int32_t value() const
	{
		return m_value;
	}

private:
	int32_t m_value;
	char    m_data[4000];
};

int main(int argc, char** argv)
{
	/*ThreadLocal* tls0 = thread_local::create();
	ThreadLocal* tls1 = thread_local::create();

	TestFunctor functor;
	Task task;

	Thread* t0 = thread::create(functor,    nullptr);
	Thread* t1 = thread::create(&Task::run, nullptr, &task);
	Thread* t2 = thread::create(free_func,  nullptr);*/

	//init_base();
	//
	//cout << BW_BASE_VERSION_STRING << endl;

	//cout << "size: " << sizeof(MyClass) << "  alignment: " << alignof(MyClass) << endl;

	//auto& palloc = memory::page_allocator();

	//PoolAllocator<MyClass>* pool = palloc.allocateObject<PoolAllocator<MyClass>>(5);

	//MyClass* myClass1 = pool->next();
	//MyClass* myClass2 = pool->next(10);
	//MyClass* myClass3 = pool->next(999);

	//cout << "Value1: " << myClass1->value() << endl;
	//cout << "Value2: " << myClass2->value() << endl;
	//cout << "Value3: " << myClass3->value() << endl;

	//pool->collect(myClass1);
	//pool->collect(myClass2);
	//pool->collect(myClass3);

	//palloc.deallocateObject<PoolAllocator<MyClass>>(pool);

	//void* mem1 = palloc.allocate(system::get_page_size() - 1);
	//void* mem2 = palloc.allocate(system::get_page_size() + 1);

	//cout << "mem1 size: " << palloc.allocatedSize(mem1) << endl;
	//cout << "mem2 size: " << palloc.allocatedSize(mem2) << endl;
	//cout << "total size: " << palloc.allocatedSize()    << endl;

	//palloc.deallocate(mem1);
	//palloc.deallocate(mem2);

 //   //BW_ASSERT(1 == 2);
	//Task task1(500, 600);
	//Task task2(100, 200);

	//g_tcmalloc.allocate(128, 4);
	//g_tcmalloc.allocate(256, 4);

	//Thread* t1 = thread::create(&Task::run, nullptr, &task1);
	//Thread* t2 = thread::create(&Task::run, nullptr, &task2);

	//thread::run(t1);
	//thread::run(t2);
	//
	//thread::wait(t1);
	//thread::wait(t2);

	//thread::destroy(t1);
	//thread::destroy(t2);

	//cout << "Shutdown" << endl;

	//shutdown_base();

	//test();


	real_t x(60.0);
	real_t y(100.0);

	return 0;
}