#include "bitwise/core/bit.h"
#include "bitwise/core/console.h"
#include "bitwise/core/cstring.h"

static const size_t kBufferSize  = 10;
static const size_t kBuffer2Size = 1024;

class MyTest
{
public:
    int number = 5;
};

template <>
void bw::cstring::to_string(const MyTest& test, char* buf, size_t bufSize, const char* options)
{
    format(buf, bufSize, "MTest={0}", test.number);
}

template <typename T>
void test_format(char* buffer, size_t bufferSize, T value)
{
    bw::cstring::format(buffer, bufferSize, "{0}\n", value);
    bw::console::write(buffer);
}

int main(int argc, char** argv)
{
    char buffer[kBufferSize];
    size_t nbChars = 0;

    bw::cstring::truncated_copy(buffer, kBufferSize, "01234567890000");
    bw::console::write_line(buffer);

    bw::cstring::copy(buffer, kBufferSize, "012345678");
    bw::console::write_line(buffer);

    bw::cstring::truncated_concatenate(buffer, kBufferSize, "abc");
    bw::console::write_line(buffer);

    nbChars = bw::cstring::truncated_cformat(buffer, kBufferSize, "%d %d", 10000, 10000);
    bw::console::write_cformat("%s (%lu)\n", buffer, nbChars);

    bw::console::write_cformat("%lu\n", bw::cstring::length("sooooo loooong"));
    bw::console::write_cformat("%lu\n", bw::cstring::truncated_cformat(buffer, kBufferSize, "%d %d", 123456, 1456666));
    bw::console::write_cformat("%lu\n", bw::cstring::cformat(buffer, kBufferSize, "%d", 123456));

    char buffer2[kBuffer2Size];

    bw::cstring::format(buffer2, kBuffer2Size, "{0}\n", 100);
    bw::console::write(buffer2);

    test_format<short>(buffer2, kBuffer2Size, 1);
    test_format<int>(buffer2, kBuffer2Size, 10);
    test_format<long>(buffer2, kBuffer2Size, 10);
    test_format<long long>(buffer2, kBuffer2Size, 10);
    test_format<unsigned short>(buffer2, kBuffer2Size, 10);
    test_format<unsigned>(buffer2, kBuffer2Size, 10);
    test_format<unsigned long>(buffer2, kBuffer2Size, 10);
    test_format<unsigned long long>(buffer2, kBuffer2Size, 10);

    test_format<uint16_t>(buffer2, kBuffer2Size, 10);

    nbChars = bw::cstring::format(buffer2, kBuffer2Size, "{0:b} | {1:b}", 64.0f, (int16_t) 10);
    bw::console::write_cformat("%s (%lu)\n", buffer2, nbChars);

    void* ptr = buffer2;
    nbChars = bw::cstring::format(buffer2, kBuffer2Size, "{0}", ptr);
    bw::console::write_cformat("%s (%lu)\n", buffer2, nbChars);

    MyTest m0;
    MyTest* mtest = &m0;

    nbChars = bw::cstring::format(buffer2, kBuffer2Size, "first format | {0}", mtest);
    bw::console::write_cformat("%s (%lu)\n", buffer2, nbChars);

    bw::bit::to_string((uint8_t) 1, buffer2, kBuffer2Size);
    bw::console::write_cformat("%s\n", buffer2);

    bw::console::write_format("Contains? {0}\n", bw::cstring::contains("abcd", 'c'));
    bw::console::write_format("Contains? {0}\n", bw::cstring::contains("abcd", "bc"));

    bw::console::write_format("Starts with? {0}\n", bw::cstring::starts_with("ab", 'b'));
    bw::console::write_format("Starts with? {0}\n", bw::cstring::starts_with("ab", "ab"));

    bw::console::write_format("Ends with? {0}\n", bw::cstring::ends_with("ab", 'a'));
    bw::console::write_format("Ends with? {0}\n", bw::cstring::ends_with("a", "a"));

    return 0;
}