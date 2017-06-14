// -----------------------------------------------------------------------------
//  Inline functions
// -----------------------------------------------------------------------------
void bw::cstring::copy(char* dest, size_t size, const char* src)
{
	::strncpy(dest, src, size);
}

// -----------------------------------------------------------------------------

void bw::cstring::concatenate(char* dest, size_t size, const char* src)
{
	::strncat(dest, src, size);
}

// -----------------------------------------------------------------------------

int bw::cstring::format_va(char* dest, size_t size, const char* fmt, va_list args)
{
	return ::vsnprintf(dest, size, fmt, args);
}

// -----------------------------------------------------------------------------

int bw::cstring::format(char* dest, size_t size, const char* fmt, ...)
{
	va_list args;
	va_start(args, fmt);

	int nbChars = bw::cstring::format_va(dest, size, fmt, args);
	
	va_end(args);

	return nbChars;
}

// -----------------------------------------------------------------------------

bool bw::cstring::equals(const char* str1, const char* str2)
{
	return ::strcmp(str1, str2) == 0;
}

// -----------------------------------------------------------------------------

bool bw::cstring::equals_ignore_case(const char* str1, const char* str2)
{
	return ::strcasecmp(str1, str2) == 0;
}

// -----------------------------------------------------------------------------

template <typename ...Args>
size_t bw::cstring::scan_format(const char* str, const char* format, Args&& ...args)
{
    return static_cast<size_t>(::sscanf(str, format, std::forward<Args>(args)...));
}