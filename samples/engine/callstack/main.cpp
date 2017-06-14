#include "bitwise/core/callstack.h"
#include "bitwise/core/console.h"

static const size_t kMaxCallStackBuffer = 4096;

class Test1
{
public:
    void testfn()
    {
        int a = 5;
        ++a;

        bw::StackFrame* frame = bw::callstack::walk();
        
        if (frame != nullptr)
        {
            char callstack[kMaxCallStackBuffer];
            bw::callstack::to_string(*frame, callstack, kMaxCallStackBuffer);
            bw::console::write(callstack);
        }
    }
};

class Test2
{
public:
    void testfn()
    {
        int b = 010;
        ++b;

        Test1 test1;
        test1.testfn();
    }
};

void testfn2()
{
    Test2 test2;
    test2.testfn();
}

void testfn1()
{
    testfn2();
}

int main(int argc, char** argv)
{
    testfn1();

    return 0;
}