#include <iostream>
#include "Bw/Foundation/Module.h"

namespace bw
{

////////////////////////////////////////////////////////////////////////////////
//  Public functions
////////////////////////////////////////////////////////////////////////////////
void InitFoundation()
{
	std::cout << "Initializing foundation (" << BW_FOUNDATION_VERSION_STRING << ")" << std::endl;
}

// -----------------------------------------------------------------------------

void ShutdownFoundation()
{
	std::cout << "Shuting down foundation" << std::endl;
}

}	// namespace bw