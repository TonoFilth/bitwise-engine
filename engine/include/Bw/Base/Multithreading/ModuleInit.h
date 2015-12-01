#ifndef BW_BASE_MULTITHREADING_MODULE_INIT_H
#define BW_BASE_MULTITHREADING_MODULE_INIT_H

#include "Bw/Base/Common/Module.h"
#include "Bw/Base/Memory/ModuleTypes.h"

namespace bw
{

////////////////////////////////////////////////////////////////////////////////
//  Initialization & shutdown
////////////////////////////////////////////////////////////////////////////////
BW_BASE_API void init_multithreading_system();
BW_BASE_API void shutdown_multithreading_system();

}   // namespace bw

#endif  // BW_BASE_MULTITHREADING_MODULE_INIT_H