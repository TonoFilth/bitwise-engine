#ifndef BW_BITWISE_MODULE_H
#define BW_BITWISE_MODULE_H

#include "Bw/Base.h"

#if defined(BW_MEMORY)
#	include "Bw/Memory.h"
#endif

namespace bw
{

////////////////////////////////////////////////////////////////////////////////
//	Engine initialization & shutdown
////////////////////////////////////////////////////////////////////////////////
BW_INLINE void Initialize()
{
	Internal::InitializeBaseModule();

#if defined(BW_MEMORY)
	Internal::InitializeMemoryModule();
#endif
}

// -----------------------------------------------------------------------------

BW_INLINE void Shutdown()
{
#if defined(BW_MEMORY)
	Internal::ShutdownMemoryModule();
#endif

	Internal::ShutdownBaseModule();
}

}	// namespace bw

#endif	// BW_BITWISE_MODULE_H