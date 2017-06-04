#include <iostream>
#include <bitwise/core.h>

inline int sum(int a, int b)
{
    BW_ASSERT(a > b);

    return a + b;
}

class Test
{
public:
    void test_fn(int nb)
    {
        //BW_ASSERT(false);
        sum(5, 10);
        sum(9, 10);
        sum(10, 10);
    }
};

void dummy()
{
    Test test;
    test.test_fn(0);
}

int main(int argc, char** argv)
{
    bw::initialize();

    dummy();

    bw::shutdown();

    return 0;
}