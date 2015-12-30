#include "Bw/Base/Multithreading/ModuleInit.h"
#include "Bw/Base/Detail/MultithreadingInternal.h"

#if defined(BW_SYSTEM_WINDOWS)
#	include <Windows.h>
#endif

namespace bw
{

////////////////////////////////////////////////////////////////////////////////
//  Public functions
////////////////////////////////////////////////////////////////////////////////
void init_multithreading_system()
{
	// We assume main thread is the thread that called the
	// engine initialization function
#if defined(BW_SYSTEM_WINDOWS)
	internal::set_main_thread_id(GetCurrentThreadId());
#endif

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