#ifndef BW_BASE_MODULE_INIT_H
#define BW_BASE_MODULE_INIT_H

#include "Bw/Base/Common/Module.h"

namespace bw
{

////////////////////////////////////////////////////////////////////////////////
//  Library initialization and shutdown
////////////////////////////////////////////////////////////////////////////////
BW_BASE_API void init_base();
BW_BASE_API void shutdown_base();

}	// namespace bw

#endif	// BW_BASE_MODULE_INIT_H