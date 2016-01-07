////////////////////////////////////////////////////////////////////////////////
//  Inline function definitions
////////////////////////////////////////////////////////////////////////////////
void bw::CString::Copy(char* dest, size_t size, const char* src)
{
	::strncpy(dest, src, size);
}

// -----------------------------------------------------------------------------

void bw::CString::Concatenate(char* dest, size_t size, const char* src)
{
	::strncat(dest, src, size);
}

// -----------------------------------------------------------------------------

int bw::CString::FormatVA(char* dest, size_t size, const char* fmt, va_list args)
{
	return ::vsnprintf(dest, size, fmt, args);
}

// -----------------------------------------------------------------------------

int bw::CString::Format(char* dest, size_t size, const char* fmt, ...)
{
	va_list args;
	va_start(args, fmt);

	int nbChars = bw::CString::FormatVA(dest, size, fmt, args);
	
	va_end(args);

	return nbChars;
}

// -----------------------------------------------------------------------------

bool bw::CString::Equals(const char* str1, const char* str2)
{
	return ::strcmp(str1, str2) == 0;
}

// -----------------------------------------------------------------------------

bool bw::CString::EqualsIgnoreCase(const char* str1, const char* str2)
{
	return ::strcasecmp(str1, str2) == 0;
}
