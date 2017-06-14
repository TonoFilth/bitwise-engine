#include "bitwise/core/console.h"
#include "bitwise/core/cstring.h"

class TestClass
{
public:
    int number() const { return m_number; }

private:
    int m_number = 5;
};

template <typename T>
size_t tmp_to_string(const T& value, const char* formatOptions, char* buffer, size_t bufferSize);

template <typename T>
size_t tmp_to_string(const T* value, const char* formatOptions, char* buffer, size_t bufferSize)
{
    if (value != nullptr)
    {
        return tmp_to_string(*value, formatOptions, buffer, bufferSize);
    }
    else
    {
        strcpy_s(buffer, bufferSize, "null");
        return strlen("null");
    }
}

template <>
size_t tmp_to_string(const TestClass& value, const char* formatOptions, char* buffer, size_t bufferSize)
{
    return sprintf_s(buffer, bufferSize, "%d", value.number());
}

template <>
size_t tmp_to_string(const std::nullptr_t& ptr, const char* formatOptions, char* buffer, size_t bufferSize)
{
    strcpy_s(buffer, bufferSize, "null");
    return strlen("null");
}

template <>
size_t tmp_to_string(const int& value, const char* formatOptions, char* buffer, size_t bufferSize)
{
    return sprintf_s(buffer, bufferSize, "%d", value);
}

template <>
size_t tmp_to_string(const int* value, const char* formatOptions, char* buffer, size_t bufferSize)
{
    return sprintf_s(buffer, bufferSize, "%d", *value);
}

template <>
size_t tmp_to_string(const char* value, const char* formatOptions, char* buffer, size_t bufferSize)
{
    bw::cstring::copy(buffer, bufferSize, value);
    return strlen(buffer);
}

size_t parse_arg_and_options(const char* c, int& argIndex, char* optionsBuffer, size_t optionsBufferSize)
{
    char argBuffer[3] { *c++, '\0', '\0' };
    size_t nbChars = 1;
    
    if (*c >= '0' && *c <= '9')
    {
        argBuffer[1] = *c++;
        ++nbChars;
    }
    
    // Bad argument format
    BW_ASSERT(*c == '}' || *c == ':');

    if (*c == ':')
    {
        ++c;
        ++nbChars;
    }
    else
    {
        *optionsBuffer = '\0';
    }

    bw::cstring::scan_cformat(argBuffer, "%d", &argIndex);

    char* oc = optionsBuffer;
    size_t osize = 0;

    while (*c != '}' && *c != '\0')
    {
        *oc++ = *c++;
        ++osize;
        ++nbChars;

        // Format options too big
        BW_ASSERT(osize < optionsBufferSize);
    }

    optionsBuffer[osize] = '\0';

    return nbChars + 1;
}

static char m_formatOptionsBuffer[8];

size_t parse_arg(size_t argi, size_t argIndex, const char* formatOptions, char* buffer, size_t bufferSize)
{
    // Argument index out of bounds
    BW_ASSERT(false);

    return 0;
}

template <typename Arg, typename ...Args>
size_t parse_arg(size_t argi, size_t argIndex, const char* formatOptions, char* buffer, size_t bufferSize, Arg& arg, Args&& ...args)
{
    if (argi == argIndex)
    {
        return tmp_to_string(std::forward<Arg>(arg), formatOptions, buffer, bufferSize);
    }
    else
    {
        return parse_arg(argi+1, argIndex, formatOptions, buffer, bufferSize, args...);
    }
}

bool validate_format(const char* format)
{
    size_t count = 0;
    
    const char* c = format;

    while (*c != '\0')
    {
        switch (*c)
        {
            case '{' :
            {
                if (*(c+1) == '{')
                {
                    ++c;
                }
                else
                {
                    ++count;
                }

                break;
            }
            case '}' :
            {
                if (*(c+1) == '}')
                {
                    ++c;
                }
                else
                {
                    --count;
                }
            }
        }

        ++c;
    }

    return count == 0;
}

template <typename ...Args>
size_t format(char* buffer, size_t bufferSize, const char* format, Args&& ...args)
{
    BW_ASSERT(validate_format(format));

    char* c = buffer;
    const char* f = format;
    char fchar = *f++;

    const char* bufferEnd = buffer + bufferSize - 1;

    size_t nbChars = 0;

    while (c < bufferEnd && fchar != '\0')
    {
        switch (fchar)
        {
            case '{' :
            {
                if (*f == '{')
                {
                    *c++ = fchar;
                    *c = *f++;
                    nbChars += 2;
                }
                else
                {
                    int argIndex;
                    f += parse_arg_and_options(f, argIndex, m_formatOptionsBuffer, 8);
                    size_t argChars = parse_arg(0, argIndex, m_formatOptionsBuffer, c, bufferSize - nbChars - 1, args...);

                    nbChars += argChars;
                    c += argChars-1;
                }
                
                break;
            }
            
            default : *c = fchar; ++nbChars; break;
        }

        fchar = *f++;
        ++c;
    }

    buffer[nbChars] = '\0';
    return (nbChars > 0 ? nbChars-1 : 0);
}

template <typename ...Args>
void test_format(char* buffer, size_t bufferSize, const char* format, Args&& ...args)
{
    size_t nbChars = ::format(buffer, bufferSize, format, std::forward<Args>(args)...);

    bw::console::write(buffer);
    bw::console::write_cformat("nbChars=%lu\n", nbChars);
}

int main(int argc, char** argv)
{
    /*bw::console::write_format("%p\n", bw::pointer::align_forward(argv, 4));
    bw::console::write_format("%p\n", bw::pointer::align_forward(argv, 8));
    bw::console::write_format("%p\n", bw::pointer::align_forward(argv, 10));
    bw::console::write_format("%p\n", bw::pointer::align_forward(argv, 16));

    int a = bw::integer::parse<int>("100");

    bw::console::write_format("%d\n", a);
    bw::console::write_format("%s\n", bw::integer::to_string(a));

    if (bw::integer::try_parse("10", a))
    {
        BW_LOG("Parsed");
    }
    else
    {
        BW_LOG("Not parsed");
    }*/

    char buffer[512];

    test_format(buffer, 512, "Num: {0}\nNum: {1}\nNum: {2}\nString={3}\n", 10, 20, 30, "Hello World");
    test_format(buffer, 512, "{3}\n", 10, 20, 30, "Hello World");
    
    TestClass test;
    TestClass* ptrTest = &test;

    test_format(buffer, 512, "{0}\n", test);
    test_format(buffer, 512, "{0}\n", ptrTest);
    test_format(buffer, 512, "{0}\n", nullptr);

    return 0;
}