#include <list>

#include "bitwise.h"

struct Test
{
    int value;

    Test(){}
    Test(int value){this->value = value;}
};

int main(int argc, char** argv)
{
    bw::initialize(argc, argv);

    std::list<void*> addresses;

    bw::TraceAllocator tracer(bw::memory::page_allocator(), "PageAllocator");

    for (int i = 0; i < 1024; ++i)
    {
        addresses.push_back(tracer.allocate(4097));
    }

    bw::console::write_format("%zu kb.\n", bw::memory::page_allocator().allocatedSize() / 1024);

    for (void* address : addresses)
    {
        tracer.deallocate(address);
    }

    bw::Array<Test> array(5);

    array.add(10);
    array.add(20);
    array.add(30);
    array.add(40);
    array.add(50);

    array.insert(2, 100);
    array.insert(array.rbegin() + 1, 200);

    bw::Array<Test> intArray = array;

    for (auto it = intArray.begin(); it != intArray.end(); ++it)
    {
        bw::console::write_format("%d\n", it->value);
    }

    for (Test item : intArray)
    {
        bw::console::write_format("%d\n", item);
    }

    for (size_t i = 0; i < intArray.count(); ++i)
    {
        bw::console::write_format("[%d] = %d\n", i, intArray[i].value);
    }

    bw::shutdown();

    return 0;
}