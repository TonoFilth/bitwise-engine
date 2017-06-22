#include "bitwise.h"

#include <list>

int main(int argc, char** argv)
{
    bw::initialize(argc, argv);

    std::list<void*> addresses;

    bw::TraceAllocator tracer(bw::memory::page_allocator(), "PageAllocator");

    for (int i = 0; i < 1024; ++i)
    {
        addresses.push_back(tracer.allocate(4097));
    }

    bw::console::write_format("{0} kb.\n", bw::memory::page_allocator().allocatedSize() / 1024);

    for (void* address : addresses)
    {
        tracer.deallocate(address);
    }

    bw::shutdown();

    return 0;
}