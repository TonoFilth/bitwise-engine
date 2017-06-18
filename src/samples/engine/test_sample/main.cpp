#include "bitwise.h"

int main(int argc, char** argv)
{
    bw::initialize(argc, argv);

    bw::console::write_line("Hello Sample");
    BW_LOG("Hello Sample");

    bw::shutdown();

    return 0;
}