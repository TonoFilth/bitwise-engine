#include "Bw/Base/ModuleInit.h"
#include "Bw/Base/Memory/ModuleInit.h"
#include "Bw/Base/Multithreading/ModuleInit.h"

namespace bw
{

////////////////////////////////////////////////////////////////////////////////
//  Public functions
////////////////////////////////////////////////////////////////////////////////
void init_base()
{
    init_memory_system();
	init_multithreading_system();
}

// -----------------------------------------------------------------------------

void shutdown_base()
{
	shutdown_multithreading_system();
    shutdown_memory_system();
}

}	// namespace bw