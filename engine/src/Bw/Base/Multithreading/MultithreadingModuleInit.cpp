#include "Bw/Base/Multithreading/ModuleInit.h"
#include "Bw/Base/_detail/MultithreadingInternal.h"

namespace bw
{

////////////////////////////////////////////////////////////////////////////////
//  Public functions
////////////////////////////////////////////////////////////////////////////////
void init_multithreading_system()
{
	internal::init_mutex_pool();
	internal::init_thread_pool();
}

// -----------------------------------------------------------------------------

void shutdown_multithreading_system()
{
	internal::destroy_thread_pool();
	internal::destroy_mutex_pool();
}

}	// namespace bw