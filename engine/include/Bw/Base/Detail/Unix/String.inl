////////////////////////////////////////////////////////////////////////////////
//  Inline function definitions
////////////////////////////////////////////////////////////////////////////////
void strcpy(char* dest, size_t size, const char* src)
{
    ::strncpy(dest, src, size);
}

// -----------------------------------------------------------------------------

void strcat(char* dest, size_t size, const char* src)
{
    ::strncat(dest, src, size);
}

// -----------------------------------------------------------------------------

i32_t vsprintf(char* dest, size_t size, const char* fmt, va_list args)
{
    return ::vsnprintf(dest, size, fmt, args);
}

// -----------------------------------------------------------------------------

i32_t stricmp(const char* str1, const char* str2)
{
    return ::strcasecmp(str1, str2);
}

// -----------------------------------------------------------------------------

i32_t sprintf(char* dest, size_t size, const char* fmt, ...)
{
    va_list args;
    va_start(args, fmt);

    i32_t nbChars = bw::vsprintf(dest, size, fmt, args);
   
    va_end(args);

    return nbChars;
}