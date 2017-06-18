#include "bitwise.h"

int main(int argc, char** argv)
{
    bw::console::write_line("Hello Sample");

    char buf[512];

    bw::real::to_string(10.0f, buf, 512, "e");

    /*float f = bw::real::min<float>();
    int nbChars = sprintf_s(buf, 512, "%e", f);

    bw::console::write_line(buf);
    bw::console::write_format("{0}\n", nbChars);

    double d = bw::real::min<double>();
    nbChars = sprintf_s(buf, 512, "%le", d);

    bw::console::write_line(buf);
    bw::console::write_format("{0}\n", nbChars);
    
    long double ld = bw::real::min<long double>();
    nbChars = sprintf_s(buf, 512, "%Lg", ld);

    bw::console::write_line(buf);
    bw::console::write_format("{0}\n", nbChars);*/

    return 0;
}