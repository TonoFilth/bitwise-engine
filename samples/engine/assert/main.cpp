#include "bitwise/core/assert.h"

void call_once()
{
    BW_CALL_ONCE();
}

void no_recursion();

void call_no_recursion()
{
    no_recursion();
}

void no_recursion()
{
    BW_NO_RECURSION();

    call_no_recursion();
}

void no_entry()
{
    BW_NO_ENTRY();
}

void unimplemented()
{
    BW_UNIMPLEMENTED();
}

void my_assert_handler(const char* expression, const char* message, const char* file, int line, bool callstack, bool halt)
{
    // Does nothing
}

int main(int argc, char** argv)
{
    //bw::assert::set_handler(my_assert_handler);
    //bw::assert::set_handler(nullptr);

    //BW_ASSERT(false);
    //BW_ASSERTM(false, "Custom message");
    //BW_ASSERTF(false, "Custom message format {0} {1}", "Hello", "World");

    //call_once();
    //call_once();

    //no_recursion();

    //no_entry();

    //unimplemented();

    return 0;
}