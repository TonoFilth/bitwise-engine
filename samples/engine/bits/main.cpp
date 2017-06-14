#include "bitwise/core/bit.h"
#include "bitwise/core/console.h"
#include "bitwise/core/cstring.h"

template <typename T>
void write(const char* message, T result)
{
    static char buf[68];

    bw::bit::to_string(result, buf, 68);
    bw::console::write_cformat("%s | %c=%s\n", message, message[0], buf);
}

int main(int argc, char** argv)
{
    uint8_t a = 0;
    uint8_t b = 0;

    bw::console::write_line("uint64_t a=0");
    bw::console::write_line("uint64_t b=0");

    bw::console::write_line("");

    a = bw::bit::toggle(a, 1);
    write("a> toggle bit 1", a);

    b = bw::bit::toggle(b, 7);
    write("b> set bit 7", b);

    a = bw::bit::complement(a);
    write("a> complement", a);

    b = bw::bit::complement(b);
    write("b> complement", b);

    bw::console::write_cformat("a> is bit 1 set? %s\n", bw::bit::is_set(a, 1) ? "true" : "false");

    a = bw::bit::set(a, 1);
    write("a> set bit 1", a);

    bw::console::write_cformat("a> is bit 1 set? %s\n", bw::bit::is_set(a, 1) ? "true" : "false");

    a = bw::bit::unset(a, 6);
    write("a> unset bit 6", a);

    char buffer[65];

    bw::bit::to_string(a, buffer, 65);
    bw::console::write_line(buffer);
    
    uint8_t multimask = bw::bit::mask<uint8_t>(0, 2, 4);
    bw::bit::to_string(multimask, buffer, 65);
    bw::console::write_line(buffer);

    uint8_t bitmask = bw::bit::mask<uint8_t>(0, 1);
    bw::bit::to_string(bitmask, buffer, 65);
    bw::console::write_format("{0:b}\n", bitmask);

    return 0;
}