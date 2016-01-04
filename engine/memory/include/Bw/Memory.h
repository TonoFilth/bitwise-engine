#ifndef BW_MEMORY_MODULE_H
#define BW_MEMORY_MODULE_H

#include "Bw/Memory/Export.h"

namespace bw
{
namespace Internal
{

////////////////////////////////////////////////////////////////////////////////
//	Public functions
////////////////////////////////////////////////////////////////////////////////
BW_MEMORY_API void InitializeMemoryModule();
BW_MEMORY_API void ShutdownMemoryModule();

}	// namespace Internal
}	// namespace bw

#endif	// BW_MEMORY_MODULE_H