#include <iostream>
#include "Bw/Base/Module.h"

#if defined(BW_SYSTEM_WINDOWS)
#	include "Bw/Base/Impl/Windows/AssertHandlerImpl.h"
#else
#   include "Bw/Base/Impl/Unix/AssertHandlerImpl.h"
#endif

namespace bw
{

////////////////////////////////////////////////////////////////////////////////
//  Public functions
////////////////////////////////////////////////////////////////////////////////
void InitBase()
{
	static AssertHandlerImpl assertHandler;

	std::cout << "Initializing base (" << BW_BASE_VERSION_STRING << ")" << std::endl;

	SetAssertHandler(assertHandler);
}

// -----------------------------------------------------------------------------

void ShutdownBase()
{
	std::cout << "Shuting down base" << std::endl;
}

}	// namespace bw