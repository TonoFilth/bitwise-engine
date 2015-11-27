#include "Bw/Base/ModuleInit.h"
#include "Bw/Base/Memory/Module.h"

namespace bw
{

////////////////////////////////////////////////////////////////////////////////
//  Public functions
////////////////////////////////////////////////////////////////////////////////
void init_base()
{
    init_memory_system();
}

// -----------------------------------------------------------------------------

void shutdown_base()
{
    shutdown_memory_system();
}

}	// namespace bw