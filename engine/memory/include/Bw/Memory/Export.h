#ifndef BW_MEMORY_EXPORT_H
#define BW_MEMORY_EXPORT_H

#include "Bw/Base/Macros.h"

#if defined(BW_MEMORY_EXPORT)
#	define BW_MEMORY_API BW_API_EXPORT
#else
#	define BW_MEMORY_API BW_API_IMPORT
#endif

#endif	// BW_MEMORY_EXPORT_H