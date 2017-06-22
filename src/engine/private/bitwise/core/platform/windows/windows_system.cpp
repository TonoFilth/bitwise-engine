#include <Windows.h>
#include "bitwise/core/system.h"
#include "bitwise/core/internal.h"
#include "bitwise/core/assert.h"

// -----------------------------------------------------------------------------
//  Constants
// -----------------------------------------------------------------------------
static const size_t kMaxErrorBuffer = 2048;

// -----------------------------------------------------------------------------
//  Private variables
// -----------------------------------------------------------------------------
static char   m_errorBuffer[kMaxErrorBuffer];
static size_t m_pageSize = 0;

namespace bw
{

// -----------------------------------------------------------------------------
//  Internal functions
// -----------------------------------------------------------------------------
void internal::system::initialize(int argc, char** argv)
{
}

// -----------------------------------------------------------------------------

void internal::system::shutdown()
{
}

// -----------------------------------------------------------------------------

const char* internal::system::get_last_error_message()
{
    size_t errorCode = ::GetLastError();

    if (errorCode == 0)
    {
        return "";
    }

    size_t size = FormatMessageA(FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS | FORMAT_MESSAGE_MAX_WIDTH_MASK,
                                 NULL, errorCode, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPSTR) &m_errorBuffer, kMaxErrorBuffer, NULL);

    if (size > 0)
    {
        return m_errorBuffer;
    }

    // TODO: Handle error
    return "";
}

////////////////////////////////////////////////////////////////////////////////
/// \details Detailed description.
/// \todo Write detailed description.
////////////////////////////////////////////////////////////////////////////////
int system::exec(const char* program, const char* args)
{
	return -1;
}

////////////////////////////////////////////////////////////////////////////////
/// \details Detailed description.
/// \todo Write detailed description.
////////////////////////////////////////////////////////////////////////////////
size_t system::page_size()
{
    if (m_pageSize != 0)
    {
        return m_pageSize;
    }

    SYSTEM_INFO info;
	GetSystemInfo(&info);

	m_pageSize = info.dwPageSize;
    return m_pageSize;
}

// -----------------------------------------------------------------------------

//size_t System::GetCacheSize()
//{
//	SYSTEM_LOGICAL_PROCESSOR_INFORMATION info[16];
//	DWORD nbProcessors = 608;
//
//	if (GetLogicalProcessorInformation(info, &nbProcessors))
//	{
//		return 1;
//	}
//	else
//	{
//		return 0;
//	}
//}

}	// namespace bw