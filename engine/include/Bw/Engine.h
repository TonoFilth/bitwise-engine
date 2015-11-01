#ifndef BW_ENGINE_H
#define BW_ENGINE_H

#include <iostream>
#include "Bw/Version.h"
#include "Bw/Base/Module.h"
#if defined(BW_FOUNDATION)
#	include "Bw/Foundation/Module.h"
#endif

namespace bw
{

////////////////////////////////////////////////////////////////////////////////
//  Public functions
////////////////////////////////////////////////////////////////////////////////
void Init()
{
	std::cout << "Initializing engine (" << BW_ENGINE_VERSION_STRING << ")" << std::endl;

	InitBase();
#if defined(BW_FOUNDATION)
	InitFoundation();
#endif
}

// -----------------------------------------------------------------------------

void Shutdown()
{
	std::cout << "Shuting down engine" << std::endl;

#if defined(BW_FOUNDATION)
	ShutdownFoundation();
#endif
	ShutdownBase();
}

}	// namespace bw

#endif	// BW_ENGINE_H