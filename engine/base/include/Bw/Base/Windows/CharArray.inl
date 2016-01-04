////////////////////////////////////////////////////////////////////////////////
//  Inline function definitions
////////////////////////////////////////////////////////////////////////////////
void bw::CharArray::Copy(char* dest, size_t size, const char* src)
{
	::strcpy_s(dest, size, src);
}

// -----------------------------------------------------------------------------

void bw::CharArray::Concatenate(char* dest, size_t size, const char* src)
{
	::strcat_s(dest, size, src);
}

// -----------------------------------------------------------------------------

int bw::CharArray::FormatVA(char* dest, size_t size, const char* fmt, va_list args)
{
	return ::vsprintf_s(dest, size, fmt, args);
}

// -----------------------------------------------------------------------------

int bw::CharArray::Format(char* dest, size_t size, const char* fmt, ...)
{
	va_list args;
	va_start(args, fmt);

	int nbChars = bw::CharArray::FormatVA(dest, size, fmt, args);
	
	va_end(args);

	return nbChars;
}

// -----------------------------------------------------------------------------

bool bw::CharArray::Equals(const char* str1, const char* str2)
{
	return ::strcmp(str1, str2) == 0;
}

// -----------------------------------------------------------------------------

bool bw::CharArray::EqualsIgnoreCase(const char* str1, const char* str2)
{
	return ::_stricmp(str1, str2) == 0;
}
