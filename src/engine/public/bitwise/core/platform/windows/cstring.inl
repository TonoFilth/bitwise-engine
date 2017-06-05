////////////////////////////////////////////////////////////////////////////////
//  Inline function definitions
////////////////////////////////////////////////////////////////////////////////
void bw::cstring::copy(char* dest, size_t size, const char* src)
{
	::strcpy_s(dest, size, src);
}

// -----------------------------------------------------------------------------

void bw::cstring::concatenate(char* dest, size_t size, const char* src)
{
	::strcat_s(dest, size, src);
}

// -----------------------------------------------------------------------------

int bw::cstring::format_va(char* dest, size_t size, const char* fmt, va_list args)
{
	return ::vsprintf_s(dest, size, fmt, args);
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
	return ::_stricmp(str1, str2) == 0;
}
