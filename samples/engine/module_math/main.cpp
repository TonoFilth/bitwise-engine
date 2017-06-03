#include <iostream>
#include <bitwise/math.h>

int main(int argc, char** argv)
{
    bw::Vector2 vector;

    vector.x = 10.0f;
    vector.y = 20.0f;

    std::cout << vector.x << ", " << vector.y << std::endl;
    std::cout << vector.unit().x << std::endl;
    
    return 0;
}