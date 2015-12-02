#include <cstdlib>
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

	// Call the following functions once all static and
	// global variables are deleted
	// IMPORTANT: These functions are called in REVERSE order
	// of registration
	atexit(shutdown_memory_system);
	atexit(shutdown_multithreading_system);
}

// -----------------------------------------------------------------------------

void shutdown_base()
{
}

}	// namespace bw