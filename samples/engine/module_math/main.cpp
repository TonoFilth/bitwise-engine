#include "bitwise/core.h"
#include "bitwise/math.h"

int main(int argc, char** argv)
{
    bw::Vector2 vector;

    vector.x = 10.0f;
    vector.y = 20.0f;

    bw::console::write_format("({0}, {1})\n", vector.x, vector.y);;
    bw::console::write_format("{0}\n", vector.unit().x);
    
    return 0;
}