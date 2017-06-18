#include "bitwise.h"

int main(int argc, char** argv)
{
    bw::initialize(argc, argv);

    bw::console::write_line("Hello Sample");
    BW_LOG("Hello Sample");

    bw::ScopeAllocator32 scopeAlloc;

    int* i = (int*) scopeAlloc.allocate(sizeof(int));
    *i = 5;

    bw::console::write_format("{0}\n", i);

    bw::shutdown();

    return 0;
}