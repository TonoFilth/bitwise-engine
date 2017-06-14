#include "bitwise/core/bit.h"
#include "bitwise/core/log.h"
#include "bitwise/core/console.h"
#include "bitwise/core/cstring.h"

inline int sum(int a, int b)
{
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

        //bw::callstack::walk();
        bw::log::enable_channel(0);
        BW_LOG_VERBOSE(0, "Hello");
        BW_LOG_VERBOSE(1, "Hello");

        bw::log::disable_channel(0);
        BW_LOG_INFO(0, "World");

        int num = 0;
        num = bw::bit::set(num, 0);
        bw::console::write_cformat("%d\n", num);

        num = bw::bit::set(num, 1);
        bw::console::write_cformat("%d\n", num);

        num = bw::bit::unset(num, 1);
        bw::console::write_cformat("%d\n", num);

        bw::console::write_cformat("%d\n", bw::bit::complement(1));
        bw::console::write_cformat("%d\n", bw::bit::complement(0));
    }
};

void dummy()
{
    Test test;
    test.test_fn(0);

    int i = 5;
}

int main(int argc, char** argv)
{
    dummy();

    return 0;
}