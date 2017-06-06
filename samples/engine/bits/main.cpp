#include <bitwise/core.h>

template <typename T>
void write(const char* message, T result)
{
    bw::console::write_format("%s | %c=%s\n", message, message[0], bw::bit::to_string(result));
}

int main(int argc, char** argv)
{
    bw::initialize();

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

    bw::console::write_format("a> is bit 1 set? %s\n", bw::bit::is_set(a, 1) ? "true" : "false");

    a = bw::bit::set(a, 1);
    write("a> set bit 1", a);

    bw::console::write_format("a> is bit 1 set? %s\n", bw::bit::is_set(a, 1) ? "true" : "false");

    a = bw::bit::unset(a, 6);
    write("a> unset bit 6", a);

    char buffer[9];

    bw::bit::to_string(buffer, 9, a);
    bw::console::write_line(buffer);

    bw::shutdown();

    return 0;
}