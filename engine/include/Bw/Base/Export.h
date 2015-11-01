#ifndef BW_BASE_EXPORT_H
#define BW_BASE_EXPORT_H

#include "Bw/Base/Preprocessor.h"

#if defined(BW_BASE_EXPORT)
#	define BW_BASE_API BW_API_EXPORT
#else
#	define BW_BASE_API BW_API_IMPORT
#endif

#endif	// BW_BASE_EXPORT_H