#include <iostream>
#include <bitwise/core.h>

int main(int argc, char** argv)
{
    bw::initialize();

    char buff[128];
    bw::cstring::format(buff, 128, "%d", bw::platform::page_size());

    bw::console::write_line(buff);

    bw::shutdown();

    return 0;
}