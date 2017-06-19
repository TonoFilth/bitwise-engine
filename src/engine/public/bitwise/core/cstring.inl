namespace bw
{

// -----------------------------------------------------------------------------
//  Default type to string conversions
// -----------------------------------------------------------------------------
template <typename T>
BW_INLINE void cstring::to_string(const T& value, char* buffer, size_t bufferSize, const char* formatOptions)
{
    static_assert(false, "Conversion from type T to string not defined. See type T.");
}

// -----------------------------------------------------------------------------

template <typename T>
BW_INLINE void cstring::to_string(const T* value, char* buffer, size_t bufferSize, const char* formatOptions)
{
    switch (*formatOptions)
    {
        case 'a' : cformat(buffer, bufferSize, "%p", value); break;

        default :
        {
            if (value != nullptr)
            {
                to_string(*value, buffer, bufferSize, formatOptions);
            }
            else
            {
                to_string(nullptr, buffer, bufferSize, formatOptions);
            }

            break;
        }
    }
}

// -----------------------------------------------------------------------------
//  Integer to string conversions
// -----------------------------------------------------------------------------
template <> void cstring::to_string(const short&              i, char* buf, size_t bufSize, const char* opts);
template <> void cstring::to_string(const int&                i, char* buf, size_t bufSize, const char* opts);
template <> void cstring::to_string(const long&               i, char* buf, size_t bufSize, const char* opts);
template <> void cstring::to_string(const long long&          i, char* buf, size_t bufSize, const char* opts);
template <> void cstring::to_string(const unsigned short&     i, char* buf, size_t bufSize, const char* opts);
template <> void cstring::to_string(const unsigned&           i, char* buf, size_t bufSize, const char* opts);
template <> void cstring::to_string(const unsigned long&      i, char* buf, size_t bufSize, const char* opts);
template <> void cstring::to_string(const unsigned long long& i, char* buf, size_t bufSize, const char* opts);

// -----------------------------------------------------------------------------
//  Floating point to string conversions
// -----------------------------------------------------------------------------
template <> void cstring::to_string(const float&       r, char* buf, size_t bufSize, const char* opts);
template <> void cstring::to_string(const double&      r, char* buf, size_t bufSize, const char* opts);
template <> void cstring::to_string(const long double& r, char* buf, size_t bufSize, const char* opts);

// -----------------------------------------------------------------------------
//  Character conversions
// -----------------------------------------------------------------------------
template <> void cstring::to_string(const char&          c,   char* buf, size_t bufSize, const char* opts);
template <> void cstring::to_string(const signed   char& c,   char* buf, size_t bufSize, const char* opts);
template <> void cstring::to_string(const unsigned char& c,   char* buf, size_t bufSize, const char* opts);
template <> void cstring::to_string(const char*          str, char* buf, size_t bufSize, const char* opts);

// -----------------------------------------------------------------------------
//  Other conversions
// -----------------------------------------------------------------------------
template <> void cstring::to_string(const bool&      boolean, char* buf, size_t bufSize, const char* opts);
template <> void cstring::to_string(const nullptr_t& null,    char* buf, size_t bufSize, const char* opts);
template <> void cstring::to_string(const void*      pointer, char* buf, size_t bufSize, const char* opts);

namespace internal
{

BW_API size_t parse_arg_and_options(const char* c, int& argIndex, const char** optionsBuffer);
BW_API bool validate_format(const char* format);

BW_INLINE void parse_arg(size_t argi, size_t argIndex, const char* formatOptions, char* buffer, size_t bufferSize)
{
    BW_ASSERT(false, "Format argument {0} missing!", argIndex);
}

template <typename Arg, typename ...Args>
BW_INLINE void parse_arg(size_t argi, size_t argIndex, const char* formatOptions, char* buffer, size_t bufferSize, Arg& arg, Args&& ...args)
{
    if (argi == argIndex)
    {
        cstring::to_string(std::forward<Arg>(arg), buffer, bufferSize, formatOptions);
    }
    else
    {
        parse_arg(argi+1, argIndex, formatOptions, buffer, bufferSize, args...);
    }
}

}   // namespace internal
}   // namespace bw

// -----------------------------------------------------------------------------
//  Inline functions
// -----------------------------------------------------------------------------
template <typename ...Args>
size_t bw::cstring::format(char* buffer, size_t bufferSize, const char* format, Args&& ...args)
{
    BW_ASSERT(bw::internal::validate_format(format), "Invalid format string \"{0}\". Make sure open/close braces are correct.", format);

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
                    *c = fchar;
                    ++f;
                    ++nbChars;
                    /**c = *f++;
                    nbChars += 2;*/
                }
                else
                {
                    int argIndex;
                    const char* formatOptions = nullptr;

                    f += bw::internal::parse_arg_and_options(f, argIndex, &formatOptions);
                    //size_t argChars = bw::internal::parse_arg(0, argIndex, formatOptions, c, bufferSize - nbChars - 1, args...);

                    size_t argChars = 0;
                    *c = '\0';

                    bw::internal::parse_arg(0, argIndex, formatOptions, c, bufferSize - nbChars - 1, args...);

                    while (*c != '\0')
                    {
                        ++c;
                        ++argChars;
                    }

                    --c;
                    nbChars += argChars;
                    //c += argChars-1;
                }
                
                break;
            }
            case '}' :
            {
                if (*f == '}')
                {
                    *c = fchar;
                    ++f;
                    ++nbChars;
                }

                break;
            }
            
            default : *c = fchar; ++nbChars; break;
        }

        fchar = *f++;
        ++c;
    }

    buffer[nbChars] = '\0';
    //return (nbChars > 0 ? nbChars-1 : 0);
    return nbChars;
}