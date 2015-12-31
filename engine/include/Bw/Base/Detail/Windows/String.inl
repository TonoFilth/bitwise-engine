////////////////////////////////////////////////////////////////////////////////
//  Inline function definitions
////////////////////////////////////////////////////////////////////////////////
void bw::Strcpy(char* dest, size_t size, const char* src)
{
	::strcpy_s(dest, size, src);
}

// -----------------------------------------------------------------------------

void bw::Strcat(char* dest, size_t size, const char* src)
{
	::strcat_s(dest, size, src);
}

// -----------------------------------------------------------------------------

int32_t bw::Vsprintf(char* dest, size_t size, const char* fmt, va_list args)
{
	return ::vsprintf_s(dest, size, fmt, args);
}

// -----------------------------------------------------------------------------

int32_t bw::Stricmp(const char* str1, const char* str2)
{
	return ::_stricmp(str1, str2);
}

// -----------------------------------------------------------------------------

int32_t bw::Sprintf(char* dest, size_t size, const char* fmt, ...)
{
	va_list args;
	va_start(args, fmt);

	int32_t nbChars = bw::Vsprintf(dest, size, fmt, args);
	
	va_end(args);

	return nbChars;
}