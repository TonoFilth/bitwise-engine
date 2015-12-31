#include "Bw/Base.h"

namespace bw
{

////////////////////////////////////////////////////////////////////////////////
//  Public functions
////////////////////////////////////////////////////////////////////////////////
void Internal::InitBase()
{
    Internal::InitMemory();
	Internal::InitMultithreading();

	// Call the following functions once all static and
	// global variables are deleted
	// IMPORTANT: These functions are called in REVERSE order
	// of registration
	//atexit(Internal::ShutdownMemoryModule);
	//atexit(shutdown_multithreading_system);
}

// -----------------------------------------------------------------------------

void Internal::QuitBase()
{
	Internal::QuitMultithreading();
	Internal::QuitMemory();
}

}	// namespace bw