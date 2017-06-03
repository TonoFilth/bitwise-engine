#include <iostream>
#include <bitwise/core.h>

int main(int argc, char** argv)
{
    std::cout << bw::cstring::equals_ignore_case("abc", "abc") << std::endl;

    return 0;
}