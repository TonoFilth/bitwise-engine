#include "bitwise/core/cstring.h"

static const size_t kFormatOptionsBufferSize = 8;

static char m_formatOptionsBuffer[kFormatOptionsBufferSize];

namespace bw
{

////////////////////////////////////////////////////////////////////////////////
/// \details Detailed description.
/// \todo Write detailed description.
////////////////////////////////////////////////////////////////////////////////
size_t internal::parse_arg_and_options(const char* c, int& argIndex, const char** optionsBuffer)
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
        *m_formatOptionsBuffer = '\0';
    }

    bw::cstring::scan_cformat(argBuffer, "%d", &argIndex);

    char* oc = m_formatOptionsBuffer;
    size_t osize = 0;

    while (*c != '}' && *c != '\0')
    {
        *oc++ = *c++;
        ++osize;
        ++nbChars;

        // Format options too big
        BW_ASSERT(osize < kFormatOptionsBufferSize);
    }

    m_formatOptionsBuffer[osize] = '\0';
    *optionsBuffer = m_formatOptionsBuffer;

    return nbChars + 1;
}

// -----------------------------------------------------------------------------

bool internal::validate_format(const char* format)
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

}	// namespace bw